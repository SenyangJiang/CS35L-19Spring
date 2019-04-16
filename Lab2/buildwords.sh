#! /bin/sh
sed 's/\?//g' |
# remove every '?'

sed 's/<u>//g' |
# remove every '<u>'

sed 's/<\/u>//g' |
# remove every '</u>'

tr '[:upper:]' '[:lower:]' |
# change every upper case to lowercase

sed "s/\`/\'/g" |
# change every ` to '

awk "/^\s*<td>[pk'mnwlha eiou]*<\/td>\s*$/ {print;}" |
# extract lines with the form A<tdX>W</td>Z as specified

sed 's/<[^>]*>//g' |
# remove all contents enclosed by <>

sed 's/^\s*//g' |
# remove all spaces before every line

sed 's/\s*$//g' |
# remove all spaces at the end of every line

tr ' ' '\n' |
# seperate more than one words on the same line

sed '/^$/d' |
# remove all empty lines

sort -u
# sort the list of words and remove any duplicate
