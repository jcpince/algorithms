#! /bin/sh

# 193. Valid Phone Numbers
# Easy
#
# Given a text file file.txt that contains list of phone numbers (one per line), write a one liner bash script to print all valid phone numbers.
#
# You may assume that a valid phone number must appear in one of the following two formats: (xxx) xxx-xxxx or xxx-xxx-xxxx. (x means a digit)
#
# You may also assume each line in the text file must not contain leading or trailing white spaces.
#
# Example:
#
# Assume that file.txt has the following content:
#
# 987-123-4567
# 123 456 7890
# (123) 456-7890
#
# Your script should output the following valid phone numbers:
#
# 987-123-4567
# (123) 456-7890

sed -n -e '/^[0-9][0-9][0-9]-[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]$\|^([0-9][0-9][0-9]) [0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]$/p' $1

# Test with:
# echo "987-123-4567
# 123 456 7890
# (123) 456-7890
# 123-456-78910" | ./valid_phone_numers.sh
# 
# expects
# 987-123-4567
# (123) 456-7890
