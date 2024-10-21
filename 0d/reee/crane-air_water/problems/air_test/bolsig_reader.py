#Find "C", going line by line, if C is found, check if character next
#to it is an integer - if it is, it is a reaction, read the rate coeff
#data that is 2 lines below it into a file and name that file the C# reaction
#designation. Add that C# designation to a list, next time it searches for 
#C, check the C# against the list, if it is there then skip and continue 
#searching the file. Use file.seek(0) to reset to beginning 
#(Or do file.seek(last_reac) where last_reac is the line number of the last
#reaction it read, and start from there. This could eliminate need to check if
#it has done the reaction already
#Repeat until end of bolsig datafile is reached.
#Function to create a datafile with the reaction designation as its name
def create_k_file(reaction_name):
    filename = "%s.txt" % reaction_name
    f = open(filename,"w+")
    f.close()
    return filename

def read_bolsig(bolsigdatafile,XSdatafile): #Takes name of bolsig data file as input
    with open(XSdatafile,"r") as fXS:
        rxns = []
        for line in fXS:
            if line.find("PROCESS:") != -1:
                rxns.append(line[11:line.find(",")])
    with open(bolsigdatafile,"r") as fbolsig:
        lines = fbolsig.readlines()
        reac_lines = [] #list of the line numbers with reactions, to be updated with each reaction read.
        kfile_names = rxns #list of the file names (C1.txt...CN.txt)
        e_mob_dif_data = []
        for i in range(len(lines)):#Find lines with the rxns, make datafiles for each
            line = lines[i]
            isreac = line.find("C") #gives -1 if "C" is not in line
            reac_num = 0 #number of reactions found in the bolsig file
            if isreac != -1:# If C is in line
                if line[isreac+1].isdigit():#Check if C is followed by a digit. if so, this is a reaction, read its data into a file
#                    reacname = line.split()[0]
#                    kfilename = create_k_file(reacname)
#                    kfilename = create_k_file(kfile_names[reac_num])
                    reac_num += 1
                    reac_lines.append(i)
#                    kfile_names.append(kfilename)
            if line.find("Mobility") != -1:
                    for k in range(i+1,i+201):
                        e_mob_dif_data.append(lines[k].split()) # list of pairs of energy and mobility data
            if line.find("Diffusion") != -1:
                num = 0
                with open("electron_mobility_diffusion.txt","w+") as f:
                    for k in range(i+1,i+201):
                        e_mob_dif_data[num].append(lines[k].split()[-1])
                        f.write("%s\t%s\t%s\n" % (e_mob_dif_data[num][0], e_mob_dif_data[num][1], e_mob_dif_data[num][2]))
                        num += 1
#Now reac_lines has the line numbers of the first header for each reaction dataset
#data columns begin 2 lines down from these headers, and are 300 lines long each, with 2 
#lines of whitespace between end of dataset and beginning of next dataset
        print(len(kfile_names))
        print(len(reac_lines))
        exit()
        for j in range(len(reac_lines)):
            f = open(kfile_names[j],"w+")
            for i in range(reac_lines[j]+2,reac_lines[j]+202):
                f.write(lines[i])
            f.close()
            
    return None

#read_bolsig("water_out.dat","water_cs.dat")
read_bolsig("bolsigdb_air_out.dat", "bolsigdb_air.dat")
