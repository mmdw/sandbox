#!/usr/bin/python

# put this shit into the pic's dir
# run it
# ???
# profit!

import os, imghdr

for root, dirs, files in os.walk('.'):
    for fname in files:
        typ = imghdr.what(os.path.join(root, fname))
        if typ:                        
            if fname.find('.') != -1:
                oldname, dot, oldext = fname.rpartition('.')
            else:
                oldname, oldext = fname, ''                

            if oldext.lower() != typ:
                os.rename(os.path.join(root, fname), os.path.join(root, oldname + '.%s' % typ))
                print('%s' % os.path.join(root, fname))
