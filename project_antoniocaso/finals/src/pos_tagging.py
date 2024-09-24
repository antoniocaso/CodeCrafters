def pos_tagging(R, S, T, E):
    """
    Allows to analize the probabilities and the roles in order to
    return the most probable configuration of roles. 

    Arguments:
        R: tuple containing roles
        S: tuple containing words
        T: Python dictionary
        E: Python dictionary

    Returns:
        Dictionary detailing the most probable role for each word. 
    """
    tags = dict()
    probs= [{}]
    paths= [[]]
    j=0
    for r in R:
        ##probs[0].append(T["Start"].get(t)*E[next(iter(E))].get(t))
        probs[0][r]=T["Start"].get(r)*E[next(iter(E))].get(r)
        new_tuple=(r,0)
        paths[0].append(new_tuple) 
    ##probs[i].append(T["Start"].get("End"))
    ##paths[i].append(0)
    for s in S:
        if(j!=0):
            probs.append(dict())
            paths.append(list())
            for r in R:
                tupla=max_prob(probs[j-1],E[s].get(r),T,r)
                probs[j][r]=tupla[0]
                tuplx=(r,tupla[1])
                paths[j].append(tuplx)
        j+=1
    for p in probs[j-1]:
        probs[(j-1)][p]*=T[p].get("End")
    roles=backword(probs[len(probs)-1],paths)
    for s in S:
        tags[s]=roles.pop(0)
    return tags


def max_prob(row,ep,T,r):
    """
    Allows to calculate the maximum probability.

    Arguments:
        row: dictionary
        ep: rational number
        T: dictionary
        r: string
    """
    max=0
    i=0
    index=0
    for p in row :
        x=ep*row.get(p)*T[p].get(r)
        if x>max:
            max=x
            index=i
        i+=1
    return (max,index)

def backword(lastrow,path):
    """
    Allows to retrace throughout the matrix in order to recover the correct roles.

    Arguments: 
        lastrow: dictionary
        path: matrix, list of lists

    Returns:
        ret: list
    """
    ret=list()
    maxp=max(lastrow.values())
    bindex=utility(lastrow,maxp)
    i=len(path)-1
    for x in range(i,-1,-1):
        ret.append(path[x][bindex][0])
        bindex=path[x][bindex][1]
    ret.reverse()
    return ret
        


def utility(dic,maxi):
    """
    Utility function used to locate the index of a certain value.

    Arguments:
        dic: dictionary
        maxi: rational number
    """
    index=0
    for key,val in dic.items():
        if(val==maxi):
            return index
        index+=1


