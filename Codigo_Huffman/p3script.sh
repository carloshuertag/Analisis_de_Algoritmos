#!/bin/bash
# sudo chmod 777 p3script.sh
./huffman_encode zip.zip >> huffman.txt
./huffman_decode zipHuff.dat zipHuffAux.txt >> huffman.txt
./huffman_encode rar.rar >> huffman.txt
./huffman_decode rarHuff.dat rarHuffAux.txt >> huffman.txt
./huffman_encode bmp.bmp >> huffman.txt
./huffman_decode bmpHuff.dat bmpHuffAux.txt >> huffman.txt
./huffman_encode ppt.ppt >> huffman.txt
./huffman_decode pptHuff.dat pptHuffAux.txt >> huffman.txt
./huffman_encode png.png >> huffman.txt
./huffman_decode pngHuff.dat pngHuffAux.txt >> huffman.txt