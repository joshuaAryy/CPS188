Ice Concentration Visualizer & Analyzer – Great Lakes

This C-based project collects, analyzes, and visualizes daily ice concentration data for the Great Lakes. It extracts key patterns from raw data files, then generates comparative graphs using GNUPlot, offering insight into ice trends across lakes and years.


Overview
The project begins with data collection — parsing raw .txt files containing daily ice coverage percentages for Lakes Superior, Michigan, Huron, Erie, Ontario, and St. Clair. Once collected, the data is cleaned, structured, and analyzed for trends such as peak concentration days and seasonal behavior.
The processed data is then visualized through automatically generated graphs, enabling a clearer understanding of how ice coverage changes over time and between lakes.


🔍 Key Features
📈 Data Analysis
Reads and parses raw data per lake and date
Identifies ice coverage trends across time (e.g., rise/fall rates, peak days)
Supports comparison between multiple years for the same lake


🖼️ Graph Creation
Generates clear line graphs using GNUPlot:
Individual lake graphs (one per year)
All-lake comparisons for a single year
Multi-year comparisons for a single lake
Outputs are high-resolution .png images with labeled axes and titles


⚙️ Performance
Fast and memory-efficient: handles multiple large datasets in one run
Automated cleanup of intermediate plot scripts (.plt files)


File                |  Purpose
ice_concentration.c | Main program logic (parsing, analysis, plotting)
ice_data_YYYY.txt   | Daily ice concentration data (included in repo)
*.png               | Generated visual outputs
*.plt               | Temporary GNUPlot scripts (removed after use)


🚀 How to Use
1. Compile the program:
   gcc -o ice_concentration ice_concentration.c
2. Run the program with one or more data files:
   ./ice_concentration ice_data_2023.txt
   ./ice_concentration ice_data_2023.txt ice_data_2022.txt 
3. View the output:
  Graphs will be created automatically in the directory.
  Each will reflect the lake, year, or comparison in the filename.


Example Outputs: 

Superior_2023.png – Ice trends for Lake Superior in 2023 

All_Lakes_2023.png – Full-lake comparison for 2023 

Ontario_All_Years.png – Yearly trends for Lake Ontario 


