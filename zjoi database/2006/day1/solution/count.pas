{$A+,B-,D+,E+,F-,G+,I+,L+,N+,O-,P-,Q-,R-,S+,T-,V+,X+}
{$M 65520,0,655360}
program A;
	const
  	dire	:array [1..6,1..2] of integer=((-1,0),(-1,-1),(0,-1),(1,0),(1,1),(0,1));
  type
  	Tmap	=	array [1..75,1..75] of byte;
  var
  	data	:array [1..2850,1..6] of byte;
    coor	:array [1..75,1..75] of integer;
    num		:array [1..2850,1..2] of byte;
    opp		:array [-1..1,-1..1] of byte;
    map		:array [1..75] of ^tmap;
    n,m,sum,time	:longint;

  procedure init;
  	var
    	i,j,k,h,t:integer;
    begin
    	fillchar(data,sizeof(Data),1);
 	    k:=0;
      for i:=1 to 75 do
      	for j:=1 to i do
          begin
          	inc(k);
						coor[i,j]:=k;
            num[k,1]:=i; num[k,2]:=j;
          end;
      opp[-1,0]:=1; opp[-1,-1]:=2; opp[0,-1]:=3;
			opp[1,0]:=4; opp[1,1]:=5; opp[0,1]:=6;
    	assign(input,'count.in');
      reset(input);
      readln(n); readln(M);
      for i:=1 to n do
      	begin
        	new(map[i]);
          fillchar(map[i]^,sizeof(map[i]^),0);
	      	for j:=1 to i-1 do
          	begin
            	map[i]^[j,j+1]:=1;
  	          map[i]^[j+1,j]:=1;
            end;
        end;
      for i:=1 to m do
      	begin
	      	readln(j,k);
          h:=opp[num[j,1]-num[k,1],num[j,2]-num[k,2]];
          data[k,h]:=0;
          h:=opp[num[k,1]-num[j,1],num[k,2]-num[j,2]];
          data[j,h]:=0;
          if (h=3) or (h=6) then
					begin
						map[num[j,1]]^[num[j,2],num[k,2]]:=0;
						map[num[j,1]]^[num[k,2],num[j,2]]:=0;
          end;
        end;
      close(input);

      for i:=1 to n do
      	for j:=1 to i do
        	for k:=1 to i do
          	for h:=1 to i do
              if (map[i]^[k,j]=1) and (map[i]^[j,h]=1) then
              map[i]^[k,h]:=1;
    end;

  procedure out;
    begin
    	assign(output,'count.out');
      rewrite(output);
      writeln(sum);
      close(output);
    end;

  procedure main;
    var
    	i,j,x,y1:integer;
		begin
     	sum:=0;
      for i:=1 to n do
      	for j:=1 to i do
        	begin
            x:=i; y1:=j;
            while (x>2) and (j<x) and (y1>1) do
              if (data[coor[x,j],1]=1)
                and (data[coor[x,y1],2]=1) then
                begin
                  dec(x); dec(y1);
                	if map[x]^[y1,j]=1 then inc(sum);
                end else break;
            x:=i; y1:=j;
            while x<n do
            	if (data[coor[x,j],4]=1)
              	and(Data[coor[x,y1],5]=1) then
								begin
                  inc(x); inc(y1);
                  if map[x]^[y1,j]=1 then inc(sum);
								end else break;
          end;
    end;

  begin
  	init;
    main;
    out;
	end.