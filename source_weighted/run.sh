echo "Compiling..."
make
echo "Running..."
if [ -n "$1" ]; then
    ./main graph.txt query.txt output.txt $1 > log.txt
else
    #./main /mnt/data/yuyang/graph.txt /mnt/data/yuyang/query.txt output_online.txt Online > log_online.txt
    #./main /mnt/data/yuyang/graph.txt /mnt/data/yuyang/query.txt output_tree.txt Tree > log_tree.txt
    #./main graph.txt query2.txt query4.txt query6.txt query8.txt query10.txt queryd3.txt queryd5.txt queryd7.txt queryd9.txt output_optimized2.txt output_optimized4.txt output_optimized6.txt output_optimized8.txt output_optimized10.txt output_optimized3.txt output_optimized5.txt output_optimized7.txt output_optimized9.txt LSC > log_LSC.txt
    #./main graph.txt query2.txt query4.txt query6.txt query8.txt query10.txt queryd3.txt queryd5.txt queryd7.txt queryd9.txt output_tree2.txt output_tree4.txt output_tree6.txt output_tree8.txt output_tree10.txt output_tree3.txt output_tree5.txt output_tree7.txt output_tree9.txt Tree > log_tree.txt
    #./main graph.txt query2.txt query4.txt query6.txt query8.txt query10.txt queryd3.txt queryd5.txt queryd7.txt queryd9.txt output_kd2.txt output_kd4.txt output_kd6.txt output_kd8.txt output_kd10.txt output_kd3.txt output_kd5.txt output_kd7.txt output_kd9.txt KD > log_kd.txt
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
    #./main graph.txt queryf9.txt output_online9b.txt Online > log_online9b.txt
    #./main graph.txt queryf7.txt output_online7b.txt Online > log_online7b.txt
    #./main graph.txt queryf5.txt output_online5b.txt Online > log_online5b.txt
    #./main graph.txt queryf3.txt output_online3b.txt Online > log_online3b.txt
    #./main graph.txt queryf1.txt output_online1b.txt Online > log_online1b.txt
    #./main graph.txt query10.txt output_online10.txt Online > log_online10.txt
    #./main graph.txt queryd9.txt output_online9.txt Online > log_online9.txt
    #./main graph.txt query8.txt output_online8.txt Online > log_online8.txt
    #./main graph.txt queryd7.txt output_online7.txt Online > log_online7.txt
    #./main graph.txt query6.txt output_online6.txt Online > log_online6.txt
    #./main graph.txt queryd5.txt output_online5.txt Online > log_online5.txt
    #./main graph.txt query4.txt output_online4.txt Online > log_online4.txt
    #./main graph.txt queryd3.txt output_online3.txt Online > log_online3.txt
    #./main graph.txt query2.txt output_online2.txt Online > log_online2.txt
    ./main graph.txt query.txt output_LSC.txt LSC > log_LSC.txt
    ./main graph.txt query.txt output_kd.txt KD > log_kd.txt
    ./main graph.txt query.txt output_tree.txt Tree > log_tree.txt
    ./main graph.txt query.txt output_measure.txt Measure > log_measure.txt
    ./main graph.txt query.txt output_online.txt Online > log_online.txt

    #./main graph.txt query.txt output_LSC20.txt LSC > log_LSC20.txt
    #./main graph.txt query.txt output_LSC40.txt LSC > log_LSC40.txt
    #./main graph.txt query.txt output_LSC60.txt LSC > log_LSC60.txt
    #./main graph.txt query.txt output_LSC80.txt LSC > log_LSC80.txt


    #./main graph.txt query.txt output_kd20.txt KD > log_kd20.txt
    #./main graph.txt query.txt output_kd40.txt KD > log_kd40.txt
    #./main graph.txt query.txt output_kd60.txt KD > log_kd60.txt
    #./main graph.txt query.txt output_kd80.txt KD > log_kd80.txt
fi