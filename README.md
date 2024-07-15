# counting-triangles

To run the source codes, you need to first have the temporal graph file, graph.txt and the query file, query.txt (We have already provided the example graph file and query file). 

For each source file, there is a makefile for compiling the source codes.

# The code of algorithms
* DOTTT: The SOTA $\delta$-temporal triangle counting algorithm, provided by Noujan Pashanasangi and C Seshadhri. The codes are in https://github.com/nojanp/temporal-triangle-counting
* source_weighted/OTTC: Our proposed noval online algorithm for $\delta$-temporal triangle counting.
* source_weighted/WT-Index: Our proposed novel index-based algorithm for $\delta$-temporal triangle counting using the wavelet tree.
* source_binary/BTTC: Our proposed noval online algorithm for binary $\delta$-temporal triangle counting.
* source_binary/KDT-Index: Our proposed novel index-based algorithm for binary $\delta$-temporal triangle counting using the kd tree.
* source_update/WT-Index: Our proposed updating algorithm for WT-Index.

The command of running these codes (after using the makefile to compile):

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

We have also provided a toy example graph file as the graph.txt.
