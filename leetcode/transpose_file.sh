#! /bin/sh

# 194. Transpose File
# Medium
#
# Given a text file file.txt, transpose its content.
#
# You may assume that each row has the same number of columns and each field is separated by the ' ' character.
#
# Example:
#
# If file.txt has the following content:
#
# name age
# alice 21
# ryan 30
#
# Output the following:
#
# name alice ryan
# age 21 30

#input='toto.txt'
input='transpose_file_input.txt'

#line_count=$(cat $input | wc -l)
#words_count=$(head -1 $input|wc -w)

awk '
{
     if (max_nf < NF)
          max_nf = NF
     max_nr = NR
     for (x = 1; x <= NF; x++)
          vector[x, NR] = $x
}

END {
     for (x = 1; x <= max_nf; x++) {
          for (y = 1; y <= max_nr; y++)
               printf("%s ", vector[x, y])
          printf("\n")
     }
}' $input | sed -e 's/[[:blank:]]*$//'
