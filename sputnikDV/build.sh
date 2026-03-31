#=================================================+
#        Executable For /deltav.s         V0
#=================================================+

#!/bin/bash
file="deltav"

nasm -f elf64 "$file.s" -o "$file.o"
ld "$file.o" -o "$file"         

if [ $? -eq 0 ]; then
    echo "Build successful: ./$file"
else
    echo "Build failed"
fi
