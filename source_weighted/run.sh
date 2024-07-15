echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1 > log.txt
else
    ./main graph.txt query.txt output_WT.txt WT > log_WT.txt
    ./main graph.txt query.txt output_OTTC.txt OTTC > log_OTTC.txt

    #./main graph.txt query.txt output_LSC20.txt LSC > log_LSC20.txt
    #./main graph.txt query.txt output_LSC40.txt LSC > log_LSC40.txt
    #./main graph.txt query.txt output_LSC60.txt LSC > log_LSC60.txt
    #./main graph.txt query.txt output_LSC80.txt LSC > log_LSC80.txt


    #./main graph.txt query.txt output_kd20.txt KD > log_kd20.txt
    #./main graph.txt query.txt output_kd40.txt KD > log_kd40.txt
    #./main graph.txt query.txt output_kd60.txt KD > log_kd60.txt
    #./main graph.txt query.txt output_kd80.txt KD > log_kd80.txt
fi