echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1 > log.txt
else
    ./main graph.txt query.txt output_kd.txt KD > log_kd.txt
    ./main graph.txt query.txt output_onlineC.txt OnlineC > log_onlineC.txt
    ./main graph.txt query.txt output_LSCc.txt LSCc > log_LSCc.txt

fi