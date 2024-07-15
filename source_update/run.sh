echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1 > log.txt
else
    ./main graph.txt query.txt output_WT.txt WT > log_WT.txt
    ./main graph.txt query.txt output_KDT.txt KDT > log_KDT.txt
fi