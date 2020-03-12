s/(check-sat-assuming (\(.*\))$/(assert \1\n(check-sat)/g
s/(set-info.*)//g
s/; EXPECT.*//g
