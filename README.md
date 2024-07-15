# counting-triangles

To run the source codes, you need to first have the temporal graph file, graph.txt and the query file, query.txt (We have already provided the example graph file and query file). 

For each source file, there is a makefile for compiling the source codes.

# The code of algorithms
* DOTTT: The SOTA $\delta$-temporal triangle counting algorithm, provided by Noujan Pashanasangi and C Seshadhri. The codes are in https://github.com/nojanp/temporal-triangle-counting
* source_weighted/OTTC: Our proposed noval online algorithm for $\delta$-temporal triangle counting.
* source_weighted/WT-Index: Our proposed novel index-based algorithm for $\delta$-temporal triangle counting using the wavelet tree.
* source_binary/BTTC: Our proposed noval online algorithm for binary $\delta$-temporal triangle counting.
* source_binary/KDT-Index: Our proposed novel index-based algorithm for binary $\delta$-temporal triangle counting using the kd tree.

The command of running these codes:

```
./main graph.txt query.txt output.txt {id} > log.txt
```

* ALGORITHM:
The id of algorithm will be running, which the id is presented as following.

|id|algorithm|
| :----: | :----: |
|OTTC|OTTC|
|WT|WT-Index|
|BTTC|BTTC|
|KDT|KDT-Index|

You may change the output file and log file as you want.
