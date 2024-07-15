echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1
else
    ./main graph.txt query.txt output_BTTC.txt BTTC > log_BTTC.txt
    ./main graph.txt query.txt output_KDT.txt KDT > log_KDT.txt
    #./main graph.txt query2.txt query4.txt query6.txt query8.txt query10.txt queryd3.txt queryd5.txt queryd7.txt queryd9.txt output_kd2.txt output_kd4.txt output_kd6.txt output_kd8.txt output_kd10.txt output_kd3.txt output_kd5.txt output_kd7.txt output_kd9.txt KD > log_kd.txt
fi