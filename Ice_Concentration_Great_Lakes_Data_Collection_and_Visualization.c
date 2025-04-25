//CPS188 Data Collection and Visualization of Ice Concentration Trends on Ontatio's Great Lakes

#include <stdio.h>
#include <math.h> 
#include <string.h>
#include <stdlib.h>

void pulldata(char *datafile){
    FILE *data = fopen(datafile,"r");
    if (!data){
        printf("the file didn't open");
        return;
    }
    char stored[100];
    int year_num[2];
    int num_year = 0;
    int year_name[2];
   
    int year_count2023 = 0, year_count2024 = 0;
    while (fscanf(data,"%s",stored)==1){
        int num = atoi(stored);
        if(num  == 2023){
            year_count2023 += 1;
        }  
        else if(num  == 2024){
            year_count2024 += 1;
        }   
    }

    if(year_count2023 != 0){
        year_name[num_year] = 2023;
        year_num[num_year++] = year_count2023;
    }
    if(year_count2024 != 0){
        year_name[num_year] = 2024;
        year_num[num_year++] = year_count2024;
    }



    rewind(data);
    int total_days = year_count2023 + year_count2024;
    printf(" count for 2023:%d\n",year_num[0]);
    printf(" count for 2024:%d\n",year_num[1]);
    int max_lake_2023 = 0, max_lake_2024 = 0,min_lake_2023 = 0, min_lake_2024 = 0,day_counter_2023,day_counter_2024;
    int max_indices[total_days];
    int year[total_days], day[total_days]; 
    double ice_sup[total_days], ice_mich[total_days], ice_erie[total_days], ice_huron[total_days], ice_ont[total_days], ice_stclr[total_days], ice_glb[total_days];


    char curr_year[100], curr_day[100], curr_ice_erie[100], curr_ice_ont[100], curr_ice_sup[100], curr_ice_mich[100], curr_ice_huron[100], curr_ice_stclr[100], curr_glb[100], storage[100]; 
    double converter; 
    int idx = 0;

// skipping the header to get values
    for(int i = 0;i < 8;i++){
        fgets(storage,100,data);
    }
// scanning the string values then converting them into integers and doubles 
    while(fscanf(data,"%s %s %s %s %s %s %s %s %s ",curr_year, curr_day, curr_ice_sup, curr_ice_mich, curr_ice_huron, curr_ice_erie, curr_ice_ont, curr_ice_stclr, curr_glb)==9){
        year[idx] = atoi(curr_year);
        day[idx] = atoi(curr_day);
        ice_sup[idx] = atof(curr_ice_sup);
        ice_mich[idx] = atof(curr_ice_mich);
        ice_erie[idx] = atof(curr_ice_erie);
        ice_huron[idx] = atof(curr_ice_huron);
        ice_ont[idx] = atof(curr_ice_ont);
        ice_stclr[idx] = atof(curr_ice_stclr);
        ice_glb[idx]= atof(curr_glb);
        idx+=1;
    }
    // put all arrays into big array, create array of names of lakes for printing, storing avgs in variables for 2023 and 2024 
    double *ice_data[7] = {ice_sup,ice_mich,ice_erie,ice_huron,ice_ont,ice_stclr,ice_glb};
    char *lake_names[7] = {"Superior", "Michigan", "Erie", "Huron", "Ontario", "St. Clair", "Global"};
    double per_ice_sup_2023, per_ice_mich_2023, per_ice_erie_2023, per_ice_huron_2023, per_ice_ont_2023, per_ice_stclr_2023, per_ice_glb_2023,max_avg_2023,max_avg_2024,min_avg_2023,min_avg_2024; 
    double per_ice_sup_2024, per_ice_mich_2024, per_ice_erie_2024, per_ice_huron_2024, per_ice_ont_2024, per_ice_stclr_2024, per_ice_glb_2024, max_avg,max_ice,year_2023_ice,year_2024_ice;


    double ice_lake_avg_2023[] = {per_ice_sup_2023,per_ice_mich_2023,per_ice_erie_2023,per_ice_huron_2023,per_ice_ont_2023,per_ice_stclr_2023,per_ice_glb_2023};
    double ice_lake_avg_2024[] = {per_ice_sup_2024,per_ice_mich_2024,per_ice_erie_2024,per_ice_huron_2024,per_ice_ont_2024,per_ice_stclr_2024,per_ice_glb_2024};
 
    int days_counter;
    int total_max_days[total_days];
    int max_counter;
    printf("\nQ1. Yearly Average Ice Concentration Percentage of Each Lake\n");
    printf("------------------------------------------------------------\n");
    printf("\n%-5s %8d Avg. Ice %8d %3s\n", "Lake", year_name[0], year_name[1],"Avg. Ice");
    printf("-------------------------------------------\n");
    for(int i = 0; i < 7;i++){ 

        double total_max = ice_data[i][0];
        max_counter = 0;
        max_ice = ice_data[i][0];
        year_2023_ice = 0, year_2024_ice = 0;     
        for(int j = 0; j < total_days; j++){
            if(year[j] == year_name[0]){
                year_2023_ice += ice_data[i][j];
                }
            
            else if(year[j]== year_name[1]){
                year_2024_ice += ice_data[i][j];
            } 
            
            }
            ice_lake_avg_2023[i] = (year_2023_ice)/year_num[0]; // This is the array with the avg for every alke in 2023
            ice_lake_avg_2024[i] = (year_2024_ice)/year_num[1]; // This is the array with the avg for every alke in 2024
            printf("%-10s |%-15.2lf |%-15.2lf\n", lake_names[i], ice_lake_avg_2023[i], ice_lake_avg_2024[i]);
            // start of finding max days 
            for(int j = 0; j < total_days;j++){
                if(ice_data[i][j] > max_ice){
                    max_ice = ice_data[i][j];
                    max_counter = 0;
                    max_indices[max_counter++] = j;
                }
                else if (ice_data[i][j] == max_ice){
                    max_indices[max_counter++] = j;
            }
            if( max_avg_2024 > max_avg_2023){
                max_avg = max_avg_2024; // This is the max avgerage of the years for all of the lakes including total 
                
            }
            else{
                max_avg = max_avg_2023; 
            } 
            

            
        }
        // printing values for Q3

    fclose(data);
    }
    


    //this is the end of loop i 
    for( int k = 0;k < 7; k++ ){
                if(ice_lake_avg_2023[k] > max_avg_2023){
                    max_avg_2023 = ice_lake_avg_2023[k];
                    max_lake_2023 = k;
                }
                if(ice_lake_avg_2024[k] > max_avg_2024){
                    max_avg_2024 = ice_lake_avg_2024[k];
                    max_lake_2024 = k;

                }
            }  
            
        
        min_avg_2023 = ice_lake_avg_2023[0],min_avg_2024 = ice_lake_avg_2024[0];
        for (int k = 1; k < 7; k++) {
            if (ice_lake_avg_2023[k] < min_avg_2023) {
                min_avg_2023 = ice_lake_avg_2023[k];
                min_lake_2023 = k;  // Store the index of the lake with the lowest average in 2023
            }
            if (ice_lake_avg_2024[k] < min_avg_2024) {
                min_avg_2024 = ice_lake_avg_2024[k];
                min_lake_2024 = k;  // Store the index of the lake with the lowest average in 2024
                }
            }
                

            

    printf("\n\nQ2. Highest and lowest \n");
    printf("------------------------------------------------------------\n");
    printf("Lake Ice Concentration for 2023:\n");
    printf("| Year | Ice Concentration | Lake Name              | Ice Concentration (%%) |\n");
    printf("|------|-------------------|------------------------|-----------------------|\n");
    printf("| 2023 | Highest           | %-22s | %2.2lf%%                 |\n", lake_names[max_lake_2023], max_avg_2023);
    printf("| 2023 | Lowest            | %-22s | %2.2lf%%                 |\n", lake_names[min_lake_2023], min_avg_2023);
    printf("\n");

    // Table for 2024
    printf("Lake Ice Concentration for 2024:\n");
    printf("| Year | Ice Concentration | Lake Name              | Ice Concentration (%%) |\n");
    printf("|------|-------------------|------------------------|-----------------------|\n");
    printf("| 2024 | Highest           | %-22s | %2.2lf%%                |\n", lake_names[max_lake_2024], max_avg_2024);
    printf("| 2024 | Lowest            | %-22s | %2.2lf%%                 |\n", lake_names[min_lake_2024], min_avg_2024);


    printf("\n\nQ3. Highest percentage ice concentration\n");
    printf("------------------------------------------------------------\n");
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < total_days;j++){
            if(ice_data[i][j] > max_ice){
                    max_ice = ice_data[i][j];
                    max_counter = 0;
                    max_indices[max_counter++] = j;
                }
                else if (ice_data[i][j] == max_ice){
                    max_indices[max_counter++] = j;
            }
            if( max_avg_2024 > max_avg_2023){
                max_avg = max_avg_2024; // This is the max avgerage of the years for all of the lakes including total 
                
            }
            else{
                max_avg = max_avg_2023; 
            } 

        }
        printf("\nLake: %s\n", lake_names[i]);
        printf("Max Ice Concentration: %.2lf%%\n", max_ice);
        printf("Occurred on:\n");
        for (int q = 0; q < max_counter; q++) {
            int index = max_indices[q];
            printf("  - Year: %d, Day: %d\n", year[index], day[index]);
        }
    }

            double tot_max =  ice_data[0][0];
            int max_loc[total_days];
            int max_lake[total_days];
            int loc_counter=0;
            for(int i = 0; i < 6;i++){
                for(int j = 0; j < total_days;j++ ){
                    if(ice_data[i][j] > tot_max){
                        tot_max = ice_data[i][j];
                    
                    }
                }
            }
            
            for(int i = 0; i < 7; i++){
                for( int j = 0; j < total_days; j++){
                    if(ice_data[i][j] == tot_max){
                        max_loc[loc_counter] = j;
                        max_lake[loc_counter++] = i;
                        
                    }
                }
            }
                printf("\n\nQ4.Lake with max Ice concentration percentage \n");
                printf("\n------------------------\n");
                printf("Max Ice Concentration: %.2lf%%\n", tot_max);
                printf("Occurred on:\n");
            for(int k = 0; k < loc_counter;k++){
                int curr_tot_max = max_lake[k];
                int curr_max_loc = max_loc[k];
                printf("\nLake: %s\n", lake_names[curr_tot_max]);
                printf("  - Year: %d, Day: %d\n", year[curr_max_loc], day[curr_max_loc]);

            }

}

void pulldata_for_7(char *datafile1, char *datafile2){
    FILE *data1 = fopen(datafile1,"r");
    if (!data1){
        printf("the file didn't open");
        return;
    }
        FILE *data2 = fopen(datafile2,"r");
    if (!data2){
        printf("the file didn't open");
        return;
    }
    char stored[100];
    int year_num[3];
    int num_year = 0;
    int year_name[3];
   
    int  year_count2023 = 0,year_count2021 = 0,year_count2022 = 0;
    while (fscanf(data1,"%s",stored)==1){
        int num = atoi(stored);
        if(num == 2021){
            year_count2021 += 1;
        }
        else if(num  == 2022){
            year_count2022 += 1;
        } 
        else if(num  == 2023){
            year_count2023 += 1;
        }   
    }
        while (fscanf(data2,"%s",stored)==1){
        int num = atoi(stored);
        if(num == 2021){
            year_count2021 += 1;
        }
        else if(num  == 2022){
            year_count2022 += 1;
        } 
        else if(num  == 2023){
            year_count2023 += 1;
        }  
    }


    if(year_count2021 != 0){
        year_name[num_year] = 2021;
        year_num[num_year++] = year_count2021;
        
    }
    if(year_count2022 != 0){
        year_name[num_year] = 2022;
        year_num[num_year++] = year_count2022;
    }
    if(year_count2023 != 0){
        year_name[num_year] = 2023;
        year_num[num_year++] = year_count2023;
    }


    rewind(data1);
    rewind(data2);
    int  total_days = year_count2023 + year_count2021 + year_count2022;
    int max_lake_2023 = 0, max_lake_2024 = 0, min_lake_2023 = 0, min_lake_2024 = 0, day_counter_2023, day_counter_2024;
    int max_indices[total_days];
    int year[total_days], day[total_days]; 
    double ice_sup[total_days], ice_mich[total_days], ice_erie[total_days], ice_huron[total_days], ice_ont[total_days], ice_stclr[total_days], ice_glb[total_days];

    char curr_year[100], curr_day[100], curr_ice_erie[100], curr_ice_ont[100], curr_ice_sup[100], curr_ice_mich[100], curr_ice_huron[100], curr_ice_stclr[100], curr_glb[100], storage[100]; 
    double converter; 
    int idx = 0;

    // skipping the header to get values
    for(int i = 0; i < 8; i++){
        fgets(storage, 100, data1);
    }
    // scanning the string values then converting them into integers and doubles 
    while(fscanf(data1,"%s %s %s %s %s %s %s %s %s ", curr_year, curr_day, curr_ice_sup, curr_ice_mich, curr_ice_huron, curr_ice_erie, curr_ice_ont, curr_ice_stclr, curr_glb) == 9){
        year[idx] = atoi(curr_year);
        day[idx] = atoi(curr_day);
        ice_sup[idx] = atof(curr_ice_sup);
        ice_mich[idx] = atof(curr_ice_mich);
        ice_erie[idx] = atof(curr_ice_erie);
        ice_huron[idx] = atof(curr_ice_huron);
        ice_ont[idx] = atof(curr_ice_ont);
        ice_stclr[idx] = atof(curr_ice_stclr);
        ice_glb[idx] = atof(curr_glb);
        idx += 1;
    }
       for(int i = 0; i < 8; i++){
        fgets(storage, 100, data2);
    }
    // scanning the string values then converting them into integers and doubles 
    while(fscanf(data2,"%s %s %s %s %s %s %s %s %s ", curr_year, curr_day, curr_ice_sup, curr_ice_mich, curr_ice_huron, curr_ice_erie, curr_ice_ont, curr_ice_stclr, curr_glb) == 9){
        year[idx] = atoi(curr_year);
        day[idx] = atoi(curr_day);
        ice_sup[idx] = atof(curr_ice_sup);
        ice_mich[idx] = atof(curr_ice_mich);
        ice_erie[idx] = atof(curr_ice_erie);
        ice_huron[idx] = atof(curr_ice_huron);
        ice_ont[idx] = atof(curr_ice_ont);
        ice_stclr[idx] = atof(curr_ice_stclr);
        ice_glb[idx] = atof(curr_glb);
        idx += 1;
    }


    
    // put all arrays into big array, create array of names of lakes for printing, storing avgs in variables for 2023 and 2024 
    double *ice_data[7] = {ice_sup, ice_mich, ice_erie, ice_huron, ice_ont, ice_stclr, ice_glb};
    char *lake_names[7] = {"Superior", "Michigan", "Erie", "Huron", "Ontario", "St. Clair", "Global"};
    double ice_lake_avg_1[7], ice_lake_avg_2[7],ice_lake_avg_3[7];
    
    printf("\nQ7. Yearly Average Ice Concentration of all data \n");
    printf("------------------------------------------------------------\n");
    printf("\n%-5s %8d Avg. Ice %8d %3s %5d %3s\n", "Lake", year_name[0], year_name[1], "Avg. Ice",year_name[2], "Avg. Ice");
    printf("----------------------------------------------------------------\n");
    double year_1_ice = 0, year_2_ice = 0,year_3_ice = 0; 
    for(int i = 0; i < 7; i++){  
        for(int j = 0; j < total_days; j++){
            if(year[j] == year_name[0]){
                year_1_ice += ice_data[i][j];
            }
            else if(year[j] == year_name[1]){
                year_2_ice += ice_data[i][j];
            } 
            else if(year[j] == year_name[2]){
                year_3_ice += ice_data[i][j];
            } 
        }
        ice_lake_avg_1[i] = (year_1_ice) / (double) year_num[0]; // This is the array with the avg for every lake in 2023
        ice_lake_avg_2[i] = (year_2_ice) / (double)year_num[1]; // This is the array with the avg for every lake in 2024
        ice_lake_avg_3[i] = (year_3_ice) / (double)year_num[2]; // This is the array with the avg for every lake in 2024
        printf("%-10s |%-15.2lf |%-15.2lf|%-15.2lf\n", lake_names[i], ice_lake_avg_1[i], ice_lake_avg_2[i],ice_lake_avg_3[i]);
    }

    fclose(data1);
    fclose(data2);
}



void createGraphs(FILE *gp, char* datafile, char* title_suffix, char* file_suffix) {
    // Lake Superior (column 3)
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'Superior%s.png'\n", file_suffix);
    fprintf(gp, "set title 'Ice Concentration on Lake Superior %s'\n", title_suffix);
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:3 with lines lw 2 title 'Superior'\n\n", datafile);
    
    // Lake Michigan (column 4)
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'Michigan%s.png'\n", file_suffix);
    fprintf(gp, "set title 'Ice Concentration on Lake Michigan %s'\n", title_suffix);
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:4 with lines lw 2 title 'Michigan'\n\n", datafile);
    
    // Lake Huron (column 5)
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'Huron%s.png'\n", file_suffix);
    fprintf(gp, "set title 'Ice Concentration on Lake Huron %s'\n", title_suffix);
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:5 with lines lw 2 title 'Huron'\n\n", datafile);
    
    // Lake Erie (column 6)
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'Erie%s.png'\n", file_suffix);
    fprintf(gp, "set title 'Ice Concentration on Lake Erie %s'\n", title_suffix);
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:6 with lines lw 2 title 'Erie'\n\n", datafile);
    
    // Lake Ontario (column 7)
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'Ontario%s.png'\n", file_suffix);
    fprintf(gp, "set title 'Ice Concentration on Lake Ontario %s'\n", title_suffix);
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:7 with lines lw 2 title 'Ontario'\n\n", datafile);
    
    // Lake St. Clair (column 8)
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'StClair%s.png'\n", file_suffix);
    fprintf(gp, "set title 'Ice Concentration on Lake St. Clair %s'\n", title_suffix);
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:8 with lines lw 2 title 'St. Clair'\n", datafile);

    // Combined plot for all lakes
    fprintf(gp, "\nset terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'IceConcentration_AllLakes%s.png'\n", file_suffix);
    fprintf(gp, "set title 'Ice Concentration on the Great Lakes %s'\n", title_suffix);
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n\n");
    fprintf(gp, "plot '%s' every ::8 using 0:3 with lines lw 2 lt 1 title 'Superior', \\\n", datafile);
    fprintf(gp, "     '%s' every ::8 using 0:4 with lines lw 2 lt 2 title 'Michigan', \\\n", datafile);
    fprintf(gp, "     '%s' every ::8 using 0:5 with lines lw 2 lt 3 title 'Huron', \\\n", datafile);
    fprintf(gp, "     '%s' every ::8 using 0:6 with lines lw 2 lt 4 title 'Erie', \\\n", datafile);
    fprintf(gp, "     '%s' every ::8 using 0:7 with lines lw 2 lt 5 title 'Ontario', \\\n", datafile);
    fprintf(gp, "     '%s' every ::8 using 0:8 with lines lw 2 lt 6 title 'St. Clair'\n", datafile);
}

void gnuplot(char *datafile) {
    // Create GNUPlot file
    FILE *gp = fopen("plot.gnuplot", "w");

    // Set general formatting: using whitespace as a separator.
    fprintf(gp, "set datafile separator whitespace\n\n");

    createGraphs(gp, datafile, "", "");

    fclose(gp);
}

void gnuplot3(char *datafile2023_24, char *datafile2022_23, char *datafile2021_22) {
    // Create GNUPlot file
    FILE *gp = fopen("plot.gnuplot", "w");

    // Set general formatting: using whitespace as a separator.
    fprintf(gp, "set datafile separator whitespace\n\n");
    
    createGraphs(gp, datafile2023_24, "in 2023-24", "_2023_24");
    createGraphs(gp, datafile2022_23, "in 2022-23", "_2022_23");
    createGraphs(gp, datafile2021_22, "in 2021-22", "_2021_22");

    // Lake Superior (column 3) _multi
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'Superior_multi.png'\n");
    fprintf(gp, "set title 'Ice Concentration on Lake Superior from 2021-22 to 2023-24'\n");
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:3 with lines lw 2 title '2023-24', \\\n", datafile2023_24);
    fprintf(gp, "     '%s' every ::8 using 0:3 with lines lw 2 title '2022-23', \\\n", datafile2022_23);
    fprintf(gp, "     '%s' every ::8 using 0:3 with lines lw 2 title '2021-22'\n\n", datafile2021_22);

    // Lake Michigan (column 4) _multi
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'Michigan_multi.png'\n");
    fprintf(gp, "set title 'Ice Concentration on Lake Michigan from 2021-22 to 2023-24'\n");
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:4 with lines lw 2 title '2023-24', \\\n", datafile2023_24);
    fprintf(gp, "     '%s' every ::8 using 0:4 with lines lw 2 title '2022-23', \\\n", datafile2022_23);
    fprintf(gp, "     '%s' every ::8 using 0:4 with lines lw 2 title '2021-22'\n\n", datafile2021_22);

    // Lake Huron (column 5) _multi
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'Huron_multi.png'\n");
    fprintf(gp, "set title 'Ice Concentration on Lake Huron from 2021-22 to 2023-24'\n");
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:5 with lines lw 2 title '2023-24', \\\n", datafile2023_24);
    fprintf(gp, "     '%s' every ::8 using 0:5 with lines lw 2 title '2022-23', \\\n", datafile2022_23);
    fprintf(gp, "     '%s' every ::8 using 0:5 with lines lw 2 title '2021-22'\n\n", datafile2021_22);

    // Lake Erie (column 6) _multi
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'Erie_multi.png'\n");
    fprintf(gp, "set title 'Ice Concentration on Lake Erie from 2021-22 to 2023-24'\n");
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:6 with lines lw 2 title '2023-24', \\\n", datafile2023_24);
    fprintf(gp, "     '%s' every ::8 using 0:6 with lines lw 2 title '2022-23', \\\n", datafile2022_23);
    fprintf(gp, "     '%s' every ::8 using 0:6 with lines lw 2 title '2021-22'\n\n", datafile2021_22);

    // Lake Ontario (column 7) _multi
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'Ontario_multi.png'\n");
    fprintf(gp, "set title 'Ice Concentration on Lake Ontario from 2021-22 to 2023-24'\n");
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:7 with lines lw 2 title '2023-24', \\\n", datafile2023_24);
    fprintf(gp, "     '%s' every ::8 using 0:7 with lines lw 2 title '2022-23', \\\n", datafile2022_23);
    fprintf(gp, "     '%s' every ::8 using 0:7 with lines lw 2 title '2021-22'\n\n", datafile2021_22);

    // Lake St. Clair (column 8) _multi
    fprintf(gp, "set terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'StClair_multi.png'\n");
    fprintf(gp, "set title 'Ice Concentration on Lake St. Clair from 2021-22 to 2023-24'\n");
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n");
    fprintf(gp, "plot '%s' every ::8 using 0:8 with lines lw 2 title '2023-24', \\\n", datafile2023_24);
    fprintf(gp, "     '%s' every ::8 using 0:8 with lines lw 2 title '2022-23', \\\n", datafile2022_23);
    fprintf(gp, "     '%s' every ::8 using 0:8 with lines lw 2 title '2021-22'\n\n", datafile2021_22);


    // Combined plot for all lakes
    fprintf(gp, "\nset terminal pngcairo enhanced\n");
    fprintf(gp, "set output 'IceConcentration_AllLakes.png'\n");
    fprintf(gp, "set title 'Ice Concentration on the Great Lakes'\n");
    fprintf(gp, "set xlabel 'Day'\n");
    fprintf(gp, "set ylabel 'Ice Concentration (%%)'\n\n");
    fprintf(gp, "plot '%s' every ::8 using 0:3 with lines lw 2 lt 1 title 'Superior', \\\n", datafile2023_24);
    fprintf(gp, "     '%s' every ::8 using 0:4 with lines lw 2 lt 2 title 'Michigan', \\\n", datafile2023_24);
    fprintf(gp, "     '%s' every ::8 using 0:5 with lines lw 2 lt 3 title 'Huron', \\\n", datafile2023_24);
    fprintf(gp, "     '%s' every ::8 using 0:6 with lines lw 2 lt 4 title 'Erie', \\\n", datafile2023_24);
    fprintf(gp, "     '%s' every ::8 using 0:7 with lines lw 2 lt 5 title 'Ontario', \\\n", datafile2023_24);
    fprintf(gp, "     '%s' every ::8 using 0:8 with lines lw 2 lt 6 title 'St. Clair'\n", datafile2023_24);

    fclose(gp);
}

int main(int argc, char **argv){
    if (!argc)
        return 1;

    pulldata("data2023_2024.dat.txt");
    pulldata_for_7("data2021_2022.dat.txt","data2022_2023.dat.txt");
    
    if (argc == 2)
        gnuplot(argv[1]);
    else if (argc == 4)
        gnuplot3(argv[1], argv[2], argv[3]);

    return 0;
}
