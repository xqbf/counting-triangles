# counting-triangles

To run the source codes, you need to first have the temporal graph file, graph.txt and the query file, query.txt (We have already provided the example graph file and query file). 

For each source file, there is a makefile for compiling the source codes.

# The code of algorithms
* DOTTT: The SOTA $\delta$-temporal triangle counting algorithm, provided by Noujan Pashanasangi and C Seshadhri. The codes are in https://github.com/nojanp/temporal-triangle-counting
* source_weighted/baseline: The adapted baseline index-based solution from TSRjoin, an algorithm from http://avantgraph.io.
* source_weighted/OTTC: Our proposed noval online algorithm for $\delta$-temporal triangle counting.
* source_weighted/WT-Index: Our proposed novel index-based algorithm for $\delta$-temporal triangle counting using the wavelet tree.
* source_binary/BTTC: Our proposed noval online algorithm for binary $\delta$-temporal triangle counting.
* source_binary/KDT-Index: Our proposed novel index-based algorithm for binary $\delta$-temporal triangle counting using the kd tree.
* source_update/WT-Index: Our proposed updating algorithm for WT-Index.

How to use it (you need to run the scripts on a Linux platform):

- Run ``graph-gen.sh`` to generate graph data automatically, which would download datasets from [SNAP](https://snap.stanford.edu/data/index.html) and [KONECT](http://konect.cc/) and process the data into ``graph.txt``:

```sh
sh graph-gen.sh
```

- Run ``query-gen.sh`` and input the size of query time windows (in proportion to ``tmax``) to generate query data automatically, which would write queries into ``query.txt``:

```sh
sh query-gen.sh \$1
```
For query generation, \$1 has several choices:
'E': evenly generate query intervals and the setting of interval length and duration is default.
'R': randomly generate query intervals and the setting of interval length and duration is default.
'A': generate different-length query intervals and the setting of duration is default.
'B': generate different-duration query intervals and the setting of interval length is default.


The command of running these codes (after using the makefile to compile):

```
./main graph.txt query.txt output.txt {id} > log.txt
```

In the graph file, each line indiactes a temporal edge following the format { $u$, $v$, $t$ }.

In the query file, each line is a query following the format { $t_s$, $t_e$, $\delta$ }.

* ALGORITHM:
The id of algorithm will be running, which the id is presented as following.

|id|algorithm|
| :----: | :----: |
|OTTC|OTTC|
|Baseline|TSRjoin|
|WT|WT-Index|
|BTTC|BTTC|
|KDT|KDT-Index|

You may change the output file and log file as you want.

# Other
The five datasets used in paper are available from:

<div style="text-align:center">
    <table>
        <tbody>
        <tr>
            <th>Name</th>
            <th>Abbr.</th>
            <th>Source</th>
        </tr>
        <tr>
            <td>email-Eu-core temporal network</td>
            <td>EM</td>
            <td rowspan="3">https://snap.stanford.edu/data/#temporal</td>
        </tr>
        <tr>
            <td>Stack Overflow temporal network</td>
            <td>ST</td>
        </tr>
        <tr>
            <td>wiki-talk temporal network</td>
            <td>WK</td>
        </tr>
        <tr>
            <td>graph500-23</td>
            <td>GR</td>
            <td>https://ldbcouncil.org/benchmarks/graphalytics/</td>
        </tr>
        <tr>
            <td>contact</td>
            <td>CT</td>
            <td>http://konect.cc/networks/contact</td>
        </tr>
        </tbody>
    </table>
</div>

We have provided a toy example graph file as the graph.txt.

We have also attached our technical report.
