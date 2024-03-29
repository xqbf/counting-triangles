echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1
else
    ./main graph.txt query.txt output_online.txt Online > log_online.txt
    ./main graph.txt query.txt output_kd.txt KD > log_kd.txt

fi