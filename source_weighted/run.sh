echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1 > log.txt
else
    #./main /mnt/data/yuyang/graph.txt /mnt/data/yuyang/query.txt output_online.txt Online > log_online.txt
    #./main /mnt/data/yuyang/graph.txt /mnt/data/yuyang/query.txt output_tree.txt Tree > log_tree.txt
    ./main graph.txt query.txt output_online.txt Online > log_online.txt
    ./main graph.txt query.txt output_tree.txt Tree > log_tree.txt
    ./main graph.txt query.txt output_array.txt Array > log_array.txt
    ./main graph.txt query.txt output_chunk.txt Chunk > log_chunk.txt
    #./main /mnt/data/yuyang/graph.txt /mnt/data/yuyang/query.txt output_chunk.txt Chunk > log_chunk.txt
fi