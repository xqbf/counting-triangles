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

  - download datasets from [SNAP](https://snap.stanford.edu/data/index.html) and [LDBCouncil](https://datasets.ldbcouncil.org) if needed,
  - automatically detect a local `graph-ct.txt` (if present) and offer it as a dataset option, and
  - process the chosen dataset into `graph.txt`.

```sh
sh graph-gen.sh
```

- Run ``query-gen.sh`` and input the size of query time windows (in proportion to ``tmax``) to generate query data automatically, which would write queries into ``query.txt``:

```sh
sh query-gen.sh $1
```
For query generation, \$1 has several options:

'E': evenly generate query intervals and the setting of interval length and duration is default.

'R': randomly generate query intervals and the setting of interval length and duration is default.

'A': generate different-length query intervals and the setting of duration is default.

'B': generate different-duration query intervals and the setting of interval length is default.
 
Note that options 'A' and 'B' will generate multiple query files since they sweep over a set of predefined interval lengths (for A) or durations (for B), and create a separate query file for each parameter setting.

The command of running these codes (after using the makefile to compile):

```
./main graph.txt query.txt output.txt {id} > log.txt
```

In the graph file, each line indiactes a temporal edge following the format { $u$, $v$, $t$ }.

In the query file, each line is a query following the format { $t_s$, $t_e$, $\delta$ }.

# Figure reproduce guideline:

To help you reproduce Figures 12–19 more directly, here is how the current scripts map to the figures:

Generate the graph datasets

```
sh graph-gen.sh
```

The script will show 5 graph options (1-5) in the menu; these are exactly the graph datasets used in Figures 12–19 (as described in the technical report). You can select each of them in turn to reproduce the corresponding curves.

Generate query workloads for each figure

After graph.txt is generated, you can run:
```
sh query-gen.sh R   # query setting used for Figures 14 and 19 (random queries)
sh query-gen.sh A   # query setting used for Figures 12 and 17 (varying interval lengths)
sh query-gen.sh B   # query setting used for Figures 13 and 18 (varying durations)
```

These options correspond to the query distributions used in the respective figures.

Index construction (Figures 15 and 16)

Figures 15 and 16 report index construction cost. These values are obtained during the index-building step on the above datasets and can be observed/logged when running the index construction scripts described in the README.


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

*Update: We include the locally preprocessed graph-ct.txt because the original dataset we used from KONECT (konect.cc) is no longer reliably accessible. By shipping a processed snapshot in graph-ct.txt and letting the script use it directly, we keep the graph generation pipeline reproducible even if the remote source is down or permanently unavailable.

We have provided a toy example graph file as the graph.txt.

We have also attached our technical report.
