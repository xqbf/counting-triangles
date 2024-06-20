echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1 > log.txt
else
    ./main graph.txt query.txt output_kd.txt KD > log_kd.txt
    ./main graph.txt query2.txt output_kd2.txt KD > log_kd2.txt
    ./main graph.txt query.txt output_tree.txt Tree > log_tree.txt
    #./main graph.txt query2.txt output_tree2.txt Tree > log_tree2.txt
    ./main graph.txt query.txt output_online.txt Online > log_online.txt
fi