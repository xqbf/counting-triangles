echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1 > log.txt
else
    ./main graph.txt query2.txt output_LSC2.txt LSC > log_LSC2.txt
    ./main graph.txt query.txt output_online.txt Online > log_online.txt
fi