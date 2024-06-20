echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1 > log.txt
else
    ./main graph.txt query.txt output_kd.txt KD > log_kd.txt
    ./main graph.txt query.txt output_onlineC.txt OnlineC > log_onlineC.txt
    ./main graph.txt query.txt output_LSCc.txt LSCc > log_LSCc.txt
    #./main graph.txt query2.txt query4.txt query6.txt query8.txt query10.txt queryd3.txt queryd5.txt queryd7.txt queryd9.txt output_optimized2.txt output_optimized4.txt output_optimized6.txt output_optimized8.txt output_optimized10.txt output_optimized3.txt output_optimized5.txt output_optimized7.txt output_optimized9.txt LSCc > log_LSCc.txt
    #./main graph.txt query2.txt query4.txt query6.txt query8.txt query10.txt queryd3.txt queryd5.txt queryd7.txt queryd9.txt output_kd2.txt output_kd4.txt output_kd6.txt output_kd8.txt output_kd10.txt output_kd3.txt output_kd5.txt output_kd7.txt output_kd9.txt KD > log_kd.txt

fi