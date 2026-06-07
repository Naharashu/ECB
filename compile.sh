if [ "$1" == "" ]; then
	echo "No input asm file"
	exit 1
fi

nasm_path=$(which nasm)

if [ nasm_path == "" ]; then
	echo "No NASM installed"
	exit 1
fi 

file="$1"

nasm "$file" -f elf64 -o "${file%.*}".o
ld "${file%.*}".o -o "${file%.*}"
