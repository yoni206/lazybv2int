import logging

from bv2int import BV2INT

class LazyBV:

    def __init__(self, filename, logger):
        self.logger = logger
        self.bv2int = BV2INT
        self.solver = Solver(name='yices')
        self.sat_checker = Solver(name='yices')
        self.init()

    def init(self):
        # assert converted formula 
        self.solver.add_assertion(And(self.formulae))
        # assert original formula with precise semantics
        self.sat_checker.add_assertion(And(self.formulae))

    def solve(self):
        while True:
            self.logger.info('Solving')
            res = self.solver.solve()
            if not res:
                print('unsat')
                break
            else:
                lemmas = self.refine()
                if not lemmas:
                    print('sat')
                    break
                else:
                    self.solver.add_assertion(And(lemmas))


    def check_sat(self):
        self.logger.info('Checking for Sat')
        # TODO: do something here
        res = self.sat_checker.solve()
        if res:
            for x in self.input_vars:
                print(v, self.sat_checker.get_value(x))
            return True
        else:
            self.sat_checker.pop()
            return False


    def refine(self):
        self.logger.info('Refining')
        lemmas= []
        # TODO: do something here
        return lemmas

