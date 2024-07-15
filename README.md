# counting-triangles

To run the source codes, you need to first have the temporal graph file, graph.txt and the query file, query.txt (We have already provided the example graph file and query file). 

For each source file, there is a makefile for compiling the source codes.

# The code of algorithms
* DOTTT: The SOTA $\delta$-temporal triangle counting algorithm, provided by Noujan Pashanasangi and C Seshadhri. The codes are in https://github.com/nojanp/temporal-triangle-counting
* 

The command of running the source codes customizedly (take the wavelet tree index as an example):

---
./main graph.txt query.txt output_tree.txt Tree > log_tree.txt
---

You may change the output file and log file as you want.
