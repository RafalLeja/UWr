```
make gprof
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 43.48      0.10     0.10   965028     0.00     0.00  find_ele_rec
 39.13      0.19     0.09        1    90.00    90.00  sort_words
  8.70      0.21     0.02                             find_ele_iter_f
  4.35      0.22     0.01   965028     0.00     0.00  h_mod
  4.35      0.23     0.01   965028     0.00     0.00  insert_string
  0.00      0.23     0.00   965029     0.00     0.00  get_token
  0.00      0.23     0.00   965029     0.00     0.00  get_word
  0.00      0.23     0.00   965028     0.00     0.00  lower1
  0.00      0.23     0.00    23706     0.00     0.00  new_ele
  0.00      0.23     0.00    23706     0.00     0.00  save_string
  0.00      0.23     0.00        7     0.00     0.00  add_int_option
  0.00      0.23     0.00        1     0.00     0.00  add_string_option
  0.00      0.23     0.00        1     0.00     0.00  find_option
  0.00      0.23     0.00        1     0.00     0.00  parse_options
  0.00      0.23     0.00        1     0.00     0.00  show_options
  0.00      0.23     0.00        1     0.00   210.00  word_freq

make gprof QUICK=1
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
 94.68      1.78     1.78   965027     0.00     0.00  find_ele_rec
  2.13      1.82     0.04   965027     0.00     0.00  h_mod
  1.60      1.85     0.03                             compare_ele
  1.06      1.87     0.02        1     0.02     0.02  sort_words
  0.53      1.88     0.01   965027     0.00     0.00  lower1
  0.00      1.88     0.00   965029     0.00     0.00  get_word
  0.00      1.88     0.00   965028     0.00     0.00  get_token
  0.00      1.88     0.00   965027     0.00     0.00  insert_string
  0.00      1.88     0.00   363039     0.00     0.00  new_ele
  0.00      1.88     0.00   363039     0.00     0.00  save_string
  0.00      1.88     0.00        8     0.00     0.00  find_option
  0.00      1.88     0.00        7     0.00     0.00  add_int_option
  0.00      1.88     0.00        1     0.00     0.00  add_string_option
  0.00      1.88     0.00        1     0.00     0.00  parse_options
  0.00      1.88     0.00        1     0.00     0.00  show_options
  0.00      1.88     0.00        1     0.00     1.85  word_freq

make gprof quick=1 find=2 (funkcja find rekurencyjna)
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
 93.38      1.41     1.41   965027     0.00     0.00  find_ele_iter_r
  1.99      1.44     0.03   965027     0.00     0.00  h_mod
  1.99      1.47     0.03                             compare_ele
  1.32      1.49     0.02        1     0.02     0.02  sort_words
  0.66      1.50     0.01   965029     0.00     0.00  get_word
  0.66      1.51     0.01   965028     0.00     0.00  get_token
  0.00      1.51     0.00   965027     0.00     0.00  insert_string
  0.00      1.51     0.00   965027     0.00     0.00  lower1
  0.00      1.51     0.00   363039     0.00     0.00  new_ele
  0.00      1.51     0.00   363039     0.00     0.00  save_string
  0.00      1.51     0.00        8     0.00     0.00  find_option
  0.00      1.51     0.00        7     0.00     0.00  add_int_option
  0.00      1.51     0.00        1     0.00     0.00  add_string_option
  0.00      1.51     0.00        1     0.00     0.00  parse_options
  0.00      1.51     0.00        1     0.00     0.00  show_options
  0.00      1.51     0.00        1     0.00     1.48  word_freq

make gprof quick=1 find=2 SIZE=1000000 (tablica hashowana o rozmiarze 1000000)
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 25.00      0.04     0.04   965027     0.00     0.00  h_mod
 25.00      0.08     0.04   965027     0.00     0.00  insert_string
 18.75      0.11     0.03   965027     0.00     0.00  lower1
 12.50      0.13     0.02   965027     0.00     0.00  find_ele_iter_r
 12.50      0.15     0.02                             compare_ele
  6.25      0.16     0.01        1    10.00    10.00  sort_words
  0.00      0.16     0.00   965029     0.00     0.00  get_word
  0.00      0.16     0.00   965028     0.00     0.00  get_token
  0.00      0.16     0.00   363039     0.00     0.00  new_ele
  0.00      0.16     0.00   363039     0.00     0.00  save_string
  0.00      0.16     0.00        8     0.00     0.00  find_option
  0.00      0.16     0.00        7     0.00     0.00  add_int_option
  0.00      0.16     0.00        1     0.00     0.00  add_string_option
  0.00      0.16     0.00        1     0.00     0.00  parse_options
  0.00      0.16     0.00        1     0.00     0.00  show_options
  0.00      0.16     0.00        1     0.00   140.00  word_freq

make gprof quick=1 find=2 SIZE=1000000 HASH=2 (hash z xorem)
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 25.00      0.03     0.03   965027     0.00     0.00  insert_string
 16.67      0.05     0.02        1    20.00    20.00  sort_words
 16.67      0.07     0.02                             compare_ele
  8.33      0.08     0.01   965029     0.00     0.00  get_word
  8.33      0.09     0.01   965028     0.00     0.00  get_token
  8.33      0.10     0.01   965027     0.00     0.00  h_xor
  8.33      0.11     0.01   965027     0.00     0.00  lower1
  8.33      0.12     0.01                             _init
  0.00      0.12     0.00   965027     0.00     0.00  find_ele_iter_r
  0.00      0.12     0.00   363039     0.00     0.00  new_ele
  0.00      0.12     0.00   363039     0.00     0.00  save_string
  0.00      0.12     0.00        8     0.00     0.00  find_option
  0.00      0.12     0.00        7     0.00     0.00  add_int_option
  0.00      0.12     0.00        1     0.00     0.00  add_string_option
  0.00      0.12     0.00        1     0.00     0.00  parse_options
  0.00      0.12     0.00        1     0.00     0.00  show_options
  0.00      0.12     0.00        1     0.00    90.00  word_freq

make gprof QUICK=1 FIND=2 SIZE=1000000 HASH=2 LOWER=1 (lepsza funkcja lower)
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 21.43      0.03     0.03   965027     0.00     0.00  find_ele_iter_r
 21.43      0.06     0.03   965027     0.00     0.00  insert_string
 21.43      0.09     0.03                             compare_ele
 14.29      0.11     0.02   965028     0.00     0.00  get_token
 14.29      0.13     0.02        1    20.00    20.00  sort_words
  7.14      0.14     0.01   965027     0.00     0.00  h_xor
  0.00      0.14     0.00   965029     0.00     0.00  get_word
  0.00      0.14     0.00   965027     0.00     0.00  lower2
  0.00      0.14     0.00   363039     0.00     0.00  new_ele
  0.00      0.14     0.00   363039     0.00     0.00  save_string
  0.00      0.14     0.00        8     0.00     0.00  find_option
  0.00      0.14     0.00        7     0.00     0.00  add_int_option
  0.00      0.14     0.00        1     0.00     0.00  add_string_option
  0.00      0.14     0.00        1     0.00     0.00  parse_options
  0.00      0.14     0.00        1     0.00     0.00  show_options
  0.00      0.14     0.00        1     0.00   110.00  word_freq

```