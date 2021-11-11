#!/bin/bash
# sudo chmod 777 p3script2.sh
./huffman_encode 1b.txt >> huffman.txt
./huffman_decode 1bHuff.dat 1bHuffAux.txt >> huffman.txt
./huffman_encode 2b.txt >> huffman.txt
./huffman_decode 2bHuff.dat 2bHuffAux.txt >> huffman.txt
./huffman_encode 3b.md >> huffman.txt
./huffman_decode 3bHuff.dat 3bHuffAux.txt >> huffman.txt
./huffman_encode 4b.c >> huffman.txt
./huffman_decode 4bHuff.dat 4bHuffAux.txt >> huffman.txt
./huffman_encode 5b.js >> huffman.txt
./huffman_decode 5bHuff.dat 5bHuffAux.txt >> huffman.txt
./huffman_encode 1kb.js >> huffman.txt
./huffman_decode 1kbHuff.dat 1kbHuffAux.txt >> huffman.txt
./huffman_encode 2kb.pdf >> huffman.txt
./huffman_decode 2kbHuff.dat 2kbHuffAux.txt >> huffman.txt
./huffman_encode 3kb.jpeg >> huffman.txt
./huffman_decode 3kbHuff.dat 3kbHuffAux.txt >> huffman.txt
./huffman_encode 4kb.jpg >> huffman.txt
./huffman_decode 4kbHuff.dat 4kbHuffAux.txt >> huffman.txt
./huffman_encode 5kb.png >> huffman.txt
./huffman_decode 5kbHuff.dat 5kbHuffAux.txt >> huffman.txt
./huffman_encode 1mb.mp3 >> huffman.txt
./huffman_decode 1mbHuff.dat 1mbHuffAux.txt >> huffman.txt
./huffman_encode 2mb.mov >> huffman.txt
./huffman_decode 2mbHuff.dat 2mbHuffAux.txt >> huffman.txt
./huffman_encode 3mb.mov >> huffman.txt
./huffman_decode 3mbHuff.dat 3mbHuffAux.txt >> huffman.txt
./huffman_encode 4mb.zip >> huffman.txt
./huffman_decode 4mbHuff.dat 4mbHuffAux.txt >> huffman.txt
./huffman_encode 5mb.mp4 >> huffman.txt
./huffman_decode 5mbHuff.dat 5mbHuffAux.txt >> huffman.txt
./huffman_encode 1gb.mkv >> huffman.txt
./huffman_decode 1gbHuff.dat 1gbHuffAux.txt >> huffman.txt
./huffman_encode 2gb.mp4 >> huffman.txt
./huffman_decode 2gbHuff.dat 2gbHuffAux.txt >> huffman.txt
./huffman_encode 3gb.MP4 >> huffman.txt
./huffman_decode 3gbHuff.dat 3gbHuffAux.txt >> huffman.txt
./huffman_encode 4gb.MP4 >> huffman.txt
./huffman_decode 4gbHuff.dat 4gbHuffAux.txt >> huffman.txt
./huffman_encode 5gb.mp4 >> huffman.txt
./huffman_decode 5gbHuff.dat 5gbHuffAux.txt >> huffman.txt