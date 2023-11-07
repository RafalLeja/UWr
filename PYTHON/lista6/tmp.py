import regex
sequence = 'afrykanerskojezyczny'
queries = [ 'afrykanerskojezycznym', 'afrykanerskojezyczni', 
            'nieafrykanerskojezyczni' ]
for q in queries:
    m = regex.search(r'(%s){e<=2}'%q, sequence)
    print('match' if m else 'nomatch')

