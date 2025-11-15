g++ query-gen.cpp -o query-gen -O3 -std=c++17

# $1: which type of query to generate: 
# 'E': evenly generate query intervals and the setting of interval length and duration is default.
# 'R': randomly generate query intervals and the setting of interval length and duration is default.
# 'A': generate different-length query intervals and the setting of duration is default.
# 'B': generate different-duration query intervals and the setting of interval length is default.
./query-gen $1