(*
 *Program:ZJOI2010_Day1_network
 *Author:Celery.T
 *Date:June 2nd,2010
 *Kind:Netflow
 *Method:Dinic & SPFA+SAP
 *State:Solved
*)

const
	mn=1001;
    oo=10000000;
type
	adj=^edge;
    edge=record
    		pnt,c,cp,w,v:longint;
            pre,opp:adj;
    	 end;
var
	link,p,cur:array[1..mn]of adj;
    d,q,stack:array[1..mn]of longint;
    l,r,top:longint;
    used:array[1..mn]of boolean;
    n,m,k,maxflow,mincost,s,t,delta:longint;

procedure addedge(a,b,c,d,e:longint);
	var x,y:adj;
    begin
    	new(x);new(y);
        x^.pnt:=b;x^.c:=c;x^.cp:=c;x^.w:=d;x^.v:=e;x^.pre:=link[a];link[a]:=x;
        y^.pnt:=a;y^.c:=0;y^.cp:=0;y^.w:=-d;y^.v:=-e;y^.pre:=link[b];link[b]:=y;
        x^.opp:=y;y^.opp:=x;
    end;

procedure init;
	var i,a,b,c,d:longint;
    begin
    	assign(input,'network.in');
        reset(input);
        readln(n,m,k);
        s:=1;t:=n;
        for i:=1 to m do
        	begin
            	readln(a,b,c,d);
                addedge(a,b,c,0,d);
            end;
		maxflow:=0;
        close(input);
    end;

function dinic_label:boolean;
	var i:longint;
    	j:adj;
    begin
    	filldword(d,sizeof(d) >> 2,oo);
        fillchar(used,sizeof(used),0);
        q[1]:=s;d[s]:=0;
        l:=0;r:=1;
        while l<>r do
        	begin
            	l:=l mod mn+1;
                i:=q[l];
                j:=link[i];
                while j<>nil do
                	begin
                    	if(j^.c>0)and(d[j^.pnt]>d[i]+1)then
                        	begin
                            	d[j^.pnt]:=d[i]+1;
                                if j^.pnt=t then exit(true);
                                r:=r mod mn+1;
                                q[r]:=j^.pnt;
                            end;
                        j:=j^.pre;
                    end;
            end;
        exit(false);
    end;

procedure dinic_augment;
	var i:longint;
    	j:adj;
    begin
    	for i:=s to t do cur[i]:=link[i];
        stack[1]:=s;
        top:=1;
        while top>0 do
        	begin
            	i:=stack[top];
                if i<>t then
                	begin
                    	j:=cur[i];
                        while j<>nil do
                        	begin
                            	if(j^.c>0)and(d[j^.pnt]=d[i]+1)then break;
                                j:=j^.pre;
                            end;
                        if j<>nil then
                        	begin
                            	inc(top);
                                stack[top]:=j^.pnt;
                                p[top]:=j;
                                cur[i]:=j;
                            end
                        else begin
                        	dec(top);
                            d[i]:=oo;
                        end;
                    end
                else begin
                	delta:=oo;
                    for i:=top downto 2 do
                    	if delta>p[i]^.c then
                        	delta:=p[i]^.c;
                    inc(maxflow,delta);
                    for i:=top downto 2 do
                    	begin
                        	dec(p[i]^.c,delta);
                            inc(p[i]^.opp^.c,delta);
                            if p[i]^.c=0 then
                            	top:=i-1;
                        end;
                end;
            end;
    end;

procedure dinic;
	begin
    	while dinic_label do
        	dinic_augment;
    end;

function spfa:boolean;
	var i:longint;
    	j:adj;
    begin
    	filldword(d,sizeof(d) >> 2,oo);
        fillchar(used,sizeof(used),0);
        q[1]:=s;d[s]:=0;
        l:=0;r:=1;
        while l<>r do
        	begin
            	l:=l mod mn+1;
                i:=q[l];
                used[i]:=false;
                j:=link[i];
                while j<>nil do
                	begin
                    	if(j^.c>0)and(d[j^.pnt]>d[i]+j^.w)then
                        	begin
                            	d[j^.pnt]:=d[i]+j^.w;
                                p[j^.pnt]:=j;
                                if not used[j^.pnt] then
                                	begin
                                    	r:=r mod mn+1;
                                        q[r]:=j^.pnt;
                                        used[j^.pnt]:=true;
                                    end;
                            end;
                        j:=j^.pre;
                    end;
            end;
        if d[t]=oo then
        	exit(false)
        else exit(true);
    end;

procedure augment;
	var i:longint;
    begin
    	i:=t;
        delta:=oo;
        while i<>s do
        	begin
            	if p[i]^.c<delta then
                	delta:=p[i]^.c;
                i:=p[i]^.opp^.pnt;
            end;
        inc(mincost,d[t]*delta);
        i:=t;
        while i<>s do
        	begin
            	dec(p[i]^.c,delta);
                inc(p[i]^.opp^.c,delta);
                i:=p[i]^.opp^.pnt;
            end;
    end;

procedure costflow;
	begin
    	while spfa do
        	augment;
    end;

procedure rebuild;
	var i:longint;
    	j:adj;
    begin
    	for i:=s to t do
        	begin
            	j:=link[i];
                while j<>nil do
                	begin
                        j^.c:=j^.cp;
                        if j^.c>0 then
                        	addedge(i,j^.pnt,oo,j^.v,0);
                        j:=j^.pre;
                    end;
            end;
        inc(t);
        addedge(n,t,maxflow+k,0,0);
        mincost:=0;
    end;

procedure main;
	begin
    	dinic;
        rebuild;
        costflow;
    end;

procedure print;
	begin
    	assign(output,'network.out');
        rewrite(output);
        writeln(maxflow,' ',mincost);
    	close(output);
    end;

begin
	init;
    main;
    print;
end.
