echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1
else
    ./main graph.txt query.txt output_online.txt Online > log_online.txt
    ./main graph.txt query2.txt output_online2.txt Online > log_online2.txt
    ./main graph.txt query4.txt output_online4.txt Online > log_online4.txt
    ./main graph.txt query6.txt output_online6.txt Online > log_online6.txt
    ./main graph.txt query8.txt output_online8.txt Online > log_online8.txt
    ./main graph.txt query10.txt output_online10.txt Online > log_online10.txt

    ./main graph.txt queryd3.txt output_online3.txt Online > log_online3.txt
    ./main graph.txt queryd5.txt output_online5.txt Online > log_online5.txt
    ./main graph.txt queryd7.txt output_online7.txt Online > log_online7.txt
    ./main graph.txt queryd9.txt output_online9.txt Online > log_online9.txt


    ./main graph.txt query.txt output_kd.txt KD > log_kd.txt
    #./main graph.txt query2.txt query4.txt query6.txt query8.txt query10.txt queryd3.txt queryd5.txt queryd7.txt queryd9.txt output_kd2.txt output_kd4.txt output_kd6.txt output_kd8.txt output_kd10.txt output_kd3.txt output_kd5.txt output_kd7.txt output_kd9.txt KD > log_kd.txt
fi