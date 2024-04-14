echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1 > log.txt
else
    #./main /mnt/data/yuyang/graph.txt /mnt/data/yuyang/query.txt output_online.txt Online > log_online.txt
    #./main /mnt/data/yuyang/graph.txt /mnt/data/yuyang/query.txt output_tree.txt Tree > log_tree.txt
    #./main graph.txt query2.txt query4.txt query6.txt query8.txt query10.txt queryd3.txt queryd5.txt queryd7.txt queryd9.txt output_optimized2.txt output_optimized4.txt output_optimized6.txt output_optimized8.txt output_optimized10.txt output_optimized3.txt output_optimized5.txt output_optimized7.txt output_optimized9.txt LSC > log_LSC.txt
    #./main graph.txt queryd3.txt queryd5.txt queryd7.txt queryd9.txt output_optimized3.txt output_optimized5.txt output_optimized7.txt output_optimized9.txt Optimized > log_optimized.txt
    #./main graph.txt query10.txt output_optimized10.txt Optimized > log_optimized10.txt
    #./main graph.txt queryd9.txt output_optimized9.txt Optimized > log_optimized9.txt
    #./main graph.txt query8.txt output_optimized8.txt Optimized > log_optimized8.txt
    #./main graph.txt queryd7.txt output_optimized7.txt Optimized > log_optimized7.txt
    #./main graph.txt query6.txt output_optimized6.txt Optimized > log_optimized6.txt
    #./main graph.txt queryd5.txt output_optimized5.txt Optimized > log_optimized5.txt
    #./main graph.txt query4.txt output_optimized4.txt Optimized > log_optimized4.txt
    #./main graph.txt queryd3.txt output_optimized3.txt Optimized > log_optimized3.txt
    #./main graph.txt query2.txt output_optimized2.txt Optimized > log_optimized2.txt
    ./main graph.txt query.txt output_LSC.txt LSC > log_LSC.txt
    ./main graph.txt query.txt output_measure.txt Measure > log_measure.txt
    ./main graph.txt query.txt output_online.txt Online > log_online.txt
fi