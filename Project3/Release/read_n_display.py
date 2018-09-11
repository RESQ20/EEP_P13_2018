# -*- coding: utf-8 -*-

# **********************************************
# *** Update or verify the following values. ***
# **********************************************


input_file = 'C:\EEP-P13\IM-Proj\TEST\Sample_transcript.txt'

def getFileName():

    with open (input_file, mode='r') as file:
        data = file.read()
        print (data)
    print (input_file)
    #return 123789456;
    return input_file;


print ("read_n_display start...")
getReturn = getFileName()
print (getReturn)
