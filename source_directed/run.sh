echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1 > log.txt
else
    ./main graph2.txt query.txt output_kd.txt KD > log_kd.txt
    ./main graph.txt query10.txt output_kd10.txt KD > log_kd10.txt
    ./main graph.txt query8.txt output_kd8.txt KD > log_kd8.txt
    ./main graph.txt query6.txt output_kd6.txt KD > log_kd6.txt
    ./main graph.txt query4.txt output_kd4.txt KD > log_kd4.txt
    ./main graph.txt query2.txt output_kd2.txt KD > log_kd2.txt
    
    ./main graph2.txt query.txt output_onlineC.txt OnlineC > log_onlineC.txt
    ./main graph.txt query2.txt output_onlineC2.txt OnlineC > log_onlineC2.txt
    ./main graph.txt query4.txt output_onlineC4.txt OnlineC > log_onlineC4.txt
    ./main graph.txt query6.txt output_onlineC6.txt OnlineC > log_onlineC6.txt
    ./main graph.txt query8.txt output_onlineC8.txt OnlineC > log_onlineC8.txt
    ./main graph.txt query10.txt output_onlineC10.txt OnlineC > log_onlineC10.txt

    ./main graph.txt query2.txt output_onlineF2.txt OnlineF > log_onlineF2.txt
    ./main graph.txt query4.txt output_onlineF4.txt OnlineF > log_onlineF4.txt
    ./main graph.txt query6.txt output_onlineF6.txt OnlineF > log_onlineF6.txt
    ./main graph.txt query8.txt output_onlineF8.txt OnlineF > log_onlineF8.txt
    ./main graph.txt query10.txt output_onlineF10.txt OnlineF > log_onlineF10.txt


    ./main graph.txt query2.txt query4.txt query6.txt query8.txt query10.txt output_LSCc2.txt output_LSCc4.txt output_LSCc6.txt output_LSCc8.txt output_LSCc10.txt LSCc > log_LSCc.txt

    ./main graph.txt query2.txt query4.txt query6.txt query8.txt query10.txt output_kd2.txt output_kd4.txt output_kd6.txt output_kd8.txt output_kd10.txt KD > log_kd.txt
    ./main graph2.txt query.txt output_onlineC.txt LSCc > log_LSCc.txt
    ./main graph.txt query2.txt output_LSCc2.txt LSCc > log_LSCc2.txt
    ./main graph.txt query4.txt output_LSCc4.txt LSCc > log_LSCc4.txt
    ./main graph.txt query6.txt output_LSCc6.txt LSCc > log_LSCc6.txt
    ./main graph.txt query8.txt output_LSCc8.txt LSCc > log_LSCc8.txt
    ./main graph.txt query10.txt output_LSCc10.txt LSCc > log_LSCc10.txt

    ./main graph.txt query2.txt output_onlineF2.txt OnlineF > log_onlineF2.txt
    ./main graph.txt query4.txt output_onlineF4.txt OnlineF > log_onlineF4.txt
    ./main graph.txt query6.txt output_onlineF6.txt OnlineF > log_onlineF6.txt
    ./main graph.txt query8.txt output_onlineF8.txt OnlineF > log_onlineF8.txt
    ./main graph.txt query10.txt output_onlineF10.txt OnlineF > log_onlineF10.txt
fi