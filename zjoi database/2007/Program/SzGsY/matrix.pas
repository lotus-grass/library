const
     max=500;
var
   t,i,n,j,k,l,ii:longint;
   q:array[0..50001] of longint;
   fa:array[0..50001] of longint;
   chk:boolean;
   v:array[0..50001] of boolean;
   a:array[1..200,1..200] of 0..1;
   len:array[0..100000] of longint;
   loc:array[0..1000,0..1000] of longint;
   link:array[0..1000,0..1000,1..2] of longint;
   cul:array[1..200,1..200] of longint;
procedure setup;
begin
     assign(input,'matrix.in');
     assign(output,'matrix.out');
     reset(input);
     rewrite(output);
end;
procedure closeit;
begin
     close(input);
     close(output);
end;
procedure build;
var
   i,j,ii:longint;
begin
     fillchar(len,sizeof(len),0);
     for i:=1 to n do
            for j:=1 to n do
          if a[i,j]=1 then
          begin
               inc(len[cul[i,j]]);
               link[cul[i,j],len[cul[i,j]],1]:=1;
               link[cul[i,j],len[cul[i,j]],2]:=cul[i,j]+l;
               loc[cul[i,j],cul[i,j]+l]:=len[cul[i,j]];
               inc(len[cul[i,j]+l]);
               link[cul[i,j]+l,len[cul[i,j]+l],1]:=0;
               link[cul[i,j]+l,len[cul[i,j]+l],2]:=cul[i,j];
               loc[cul[i,j]+l,cul[i,j]]:=len[cul[i,j]+l];
               for ii:=1 to n do
            begin
               if ii<>j then
               begin
                    if a[i,ii]=1 then
                     begin
                          inc(len[cul[i,ii]]);
                          link[cul[i,ii],len[cul[i,ii]],1]:=1;
                          link[cul[i,ii],len[cul[i,ii]],2]:=cul[i,j]+l;
                          loc[cul[i,ii],cul[i,j]+l]:=len[cul[i,ii]];
                          inc(len[cul[i,j]+l]);
                          link[cul[i,j]+l,len[cul[i,j]+l],1]:=0;
                          link[cul[i,j]+l,len[cul[i,j]+l],2]:=cul[i,ii];
                          loc[cul[i,j]+l,cul[i,ii]]:=len[cul[i,j]+l];
                     end;
               end;
               if ii<>i then
               begin
                    if a[ii,j]=1 then
                    begin
                          inc(len[cul[ii,j]]);
                          link[cul[ii,j],len[cul[ii,j]],1]:=1;
                          link[cul[ii,j],len[cul[ii,j]],2]:=cul[i,j]+l;
                          loc[cul[ii,j],cul[i,j]+l]:=len[cul[ii,j]];
                          inc(len[cul[i,j]+l]);
                          link[cul[i,j]+l,len[cul[i,j]+l],1]:=0;
                          link[cul[i,j]+l,len[cul[i,j]+l],2]:=cul[ii,j];
                          loc[cul[i,j]+l,cul[ii,j]]:=len[cul[ii,j]+l];
                    end;
               end;
            end;
          end;
       for i:=1 to n do
        for j:=1 to n do
       if a[i,j]=1 then
       begin
               inc(len[cul[i,j]]);
               link[cul[i,j],len[cul[i,j]],1]:=0;
               link[cul[i,j],len[cul[i,j]],2]:=0;
               loc[cul[i,j],0]:=len[cul[i,j]];
               inc(len[0]);
               link[0,len[0],1]:=1;
               link[0,len[0],2]:=cul[i,j];
               loc[0,cul[i,j]]:=len[0];
               inc(len[2*l+1]);
               link[2*l+1,len[2*l+1],1]:=0;
               link[2*l+1,len[2*l+1],2]:=cul[i,j]+l;
               loc[2*l+1,cul[i,j]+l]:=len[2*l+1];
               inc(len[cul[i,j]+l]);
               link[cul[i,j]+l,len[cul[i,j]+l],1]:=1;
               link[cul[i,j]+l,len[cul[i,j]+l],2]:=2*l+1;
               loc[cul[i,j]+l,2*l+1]:=len[cul[i,j]+l];
       end;
end;
procedure BFS;
var
   head,tail,now:longint;
begin
     head:=1;tail:=1;
     fillchar(v,sizeof(v),false);
     fa[0]:=0;
     q[1]:=0;
     v[0]:=true;
     chk:=false;
     while head<=tail do
      begin
           for i:=1 to len[q[head]] do
           if (not(v[link[q[head],i,2]]))and
              (link[q[head],i,1]<>0) then
            begin
                 v[link[q[head],i,2]]:=true;
                 inc(tail);
                 q[tail]:=link[q[head],i,2];
                 fa[tail]:=head;
                 if q[tail]=2*l+1 then
                  begin
                       now:=tail;
                       repeat
                             if fa[now]=0 then break;
                             link[q[fa[now]],loc[q[fa[now]],q[now]],1]:=0;
                             link[q[now],loc[q[now],q[fa[now]]],1]:=1;
                             now:=fa[now];
                       until false;
                       chk:=true;
                       exit;
                  end;
            end;
            inc(head);
      end;
end;
procedure network_flow;
var
   i,sum:longint;
begin
     BFS;
     while chk do BFS;
     sum:=0;
     for i:=1 to l do
       if link[i,loc[i,0],1]=1 then inc(sum);
     if sum>=n then
       writeln('Yes')
               else
       writeln('No');
end;
begin
     setup;
     readln(t);
     for k:=1 to t do
     begin
          readln(n);
          l:=0;
          for i:=1 to n do
           for j:=1 to n do
          begin
              read(a[i,j]);
              if a[i,j]=1 then
               begin
                    inc(l);
                    cul[i,j]:=l;
               end;
          end;
          if l<n then
             begin
                 writeln('No');
                 continue;
             end;
          build;
          network_flow;
     end;
     closeit;
end.