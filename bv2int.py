import logging

from pysmt.walkers import IdentityDagWalker, handles
from pysmt.shortcuts import get_env
from pysmt.typing import INT

import pysmt.operators as pysmt_op

class BV2INT(IdentityDagWalker):

    def __init__(self, env=None, conf):
        if env is None:
            self.env = get_env()
        else:
            self.env = env
        IdentityDagWalker.__init__(self, env=self.env)
        self.mgr = self.env.formula_manager
        self.conf = conf
        self.symbol_map = dict()
        self.fbvand = self.mgr.Symbol(
            "fbvand", FunctionType(INT, (INT, INT, INT)))
        self.extra_constraints = set()
        self.zero = self.mgr.Int(0)

    def store_width_bounds(self, x, width):
        self.extra_constraints.add(self.mgr.GE(x, self.zero))
        self.extra_constraints.add(self.mgr.LT(x, self.mgr.Int(2 ** width)))
        
    @handles(pysmt_op.SYMBOL)
    def walk_symbol(self, formula, args, **kwargs):
        name = formula.symbol_name()
        s = self.symbol_map[name]
        if s is None:
            new_symbol = self.mgr.Symbol(name + "_nia", INT)
            width = formula.bv_width()
            self.store_width_bounds(new_symbol, width)
            return new_symbol
        else:
            return s

    @handles(pysmt_op.BV_CONSTANT)
    def walk_bv_constant(self, formula, **kwargs):
        return self.mgr.Int(formula.constant_value())

    def expand_bv_bitwise_op(self, formula, args, op):
        # TODO: implement
        bvsize = formula.bv_width()
        gran = self.conf.bv_bitwise_gran
        while bvsize % gran != 0:
            gran -= 1
        assert(gran >= 1)
        num_mono = formula.bv_width() / gran
        sum = []
        for i in range(num_mono):
            u = (i+1)*gran - 1
            l = i*gran
            e0 = self.extract_term(arg[0], u, l)
            e1 = self.extract_term(arg[1], u, l)
            block = FreshSymbol(INT,
                                "_".join(["block", str(op), str(u), str(l)]))
            sum.append(self.mgr.Times(block, Int(2 ** i))
            self.extra_constraints.add(
                self.mgr.Equals(block, self.compute_block(gran, op, e0, e1)))
        sum = self.mgr.Plus(sum)
        return sum


    def expand_bv_and(self, formula, args):
        return self.expand_bv_bitwise_op(formula, args, pysmt_op.BV_AND)


    @handles(pysmt_op.BV_AND)
    def walk_bv_and(self, formula, args, **kwargs):
        # potential candidate for abstraction
        if self.conf.abstract_bvand:
            return self.mgr.Function(self.fbvand, (formula.bv_width(), args[0], arg[1]))
        else:
            # TODO: expand_bv_and function
            return self.expand_bv_and(formula, args)

    @handles(pysmt_op.BV_NOT)
    def walk_bv_not(self, formula, args, **kwargs):
        width = formula.bv_width()
        return self.mgr.Minus(self.Int(2 ** width - 1), args[0])

    @handles(pysmt_op.BV_NEG)
    def walk_bv_neg(self, formula, args, **kwargs):
        width = formula.bv_width()
        zero_cond = self.mgr.Equals(args[0], self.zero)
        return self.mgr.ITE(zero_cond, self.zero,
                            self.mgr.Minus(self.Int(2 ** width), args[0]))

    @handles(pysmt_op.BV_OR)
    def walk_bv_or(self, formula, args, **kwargs):
        pass

    @handles(pysmt_op.BV_XOR)
    def walk_bv_xor(self, formula, args, **kwargs):
        pass

    @handles(pysmt_op.BV_ADD)
    def walk_bv_add(self, formula, args, **kwargs):
        width = formula.bv_width()
        add_term = self.mgr.Plus(args[0], args[1])
        limit = self.mgr.Int(2 ** width)
        overflow_cond = self.mgr.GE(add_term, limit)
        return self.mgr.ITE(overflow_cond,
                            self.mgr.Minus(add_term, limit), add_term)

    @handles(pysmt_op.BV_SUB)
    def walk_bv_sub(self, formula, args, **kwargs):
        second = self.walk_bv_neg(formula, args[1], **kwargs)
        return self.walk_bv_add(formula, args[0], second, **kwargs)

    @handles(pysmt_op.BV_MUL)
    def walk_bv_mul(self, formula, args, **kwargs):
        return self.mgr.BVMul(args[0], args[1])

    @handles(pysmt_op.BV_UDIV)
    def walk_bv_udiv(self, formula, args, **kwargs):
        return self.mgr.BVUDiv(args[0], args[1])

    @handles(pysmt_op.BV_UREM)
    def walk_bv_urem(self, formula, args, **kwargs):
        return self.mgr.BVURem(args[0], args[1])

    @handles(pysmt_op.BV_ULT)
    def walk_bv_ult(self, formula, args, **kwargs):
        return self.mgr.BVULT(args[0], args[1])

    @handles(pysmt_op.BV_ULE)
    def walk_bv_ule(self, formula, args, **kwargs):
        return self.mgr.BVULE(args[0], args[1])

    @handles(pysmt_op.BV_EXTRACT)
    def walk_bv_extract(self, formula, args, **kwargs):
        return self.mgr.BVExtract(args[0],
                                  start=formula.bv_extract_start(),
                                  end=formula.bv_extract_end())

    @handles(pysmt_op.BV_ROR)
    def walk_bv_ror(self, formula, args, **kwargs):
        return self.mgr.BVRor(args[0], formula.bv_rotation_step())

    @handles(pysmt_op.BV_ROL)
    def walk_bv_rol(self, formula, args, **kwargs):
        return self.mgr.BVRol(args[0], formula.bv_rotation_step())

    @handles(pysmt_op.BV_SEXT)
    def walk_bv_sext(self, formula, args, **kwargs):
        return self.mgr.BVSExt(args[0], formula.bv_extend_step())

    @handles(pysmt_op.BV_ZEXT)
    def walk_bv_zext(self, formula, args, **kwargs):
        return self.mgr.BVZExt(args[0], formula.bv_extend_step())

    @handles(pysmt_op.BV_CONCAT)
    def walk_bv_concat(self, formula, args, **kwargs):
        return self.mgr.BVConcat(args[0], args[1])

    @handles(pysmt_op.BV_LSHL)
    def walk_bv_lshl(self, formula, args, **kwargs):
        return self.mgr.BVLShl(args[0], args[1])

    @handles(pysmt_op.BV_LSHR)
    def walk_bv_lshr(self, formula, args, **kwargs):
        return self.mgr.BVLShr(args[0], args[1])

    @handles(pysmt_op.BV_ASHR)
    def walk_bv_ashr(self, formula, args, **kwargs):
        return self.mgr.BVAShr(args[0], args[1])

    @handles(pysmt_op.BV_COMP)
    def walk_bv_comp(self, formula, args, **kwargs):
        return self.mgr.BVComp(args[0], args[1])

    @handles(pysmt_op.BV_SLT)
    def walk_bv_slt(self, formula, args, **kwargs):
        return self.mgr.BVSLT(args[0], args[1])

    @handles(pysmt_op.BV_SLE)
    def walk_bv_sle(self, formula, args, **kwargs):
        return self.mgr.BVSLE(args[0], args[1])

    @handles(pysmt_op.BV_SDIV)
    def walk_bv_sdiv(self, formula, args, **kwargs):
        return self.mgr.BVSDiv(args[0], args[1])

    @handles(pysmt_op.BV_SREM)
    def walk_bv_srem(self, formula, args, **kwargs):
        return self.mgr.BVSRem(args[0], args[1])
