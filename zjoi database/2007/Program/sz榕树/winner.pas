const maxn=300;

var n,m,i,j,k,min,result:longint;
    a,b:array[1..maxn]of longint;
    c:array[1..maxn,0..1]of longint;
    e:array[1..maxn,1..maxn]of boolean;
    bool:boolean;
begin
     assign(input,'winner.in');
     reset(input);
     assign(output,'winner.out');
     rewrite(output);
     readln(n,m);
     for i:=1 to n do
     begin
       read(a[i]);
       b[i]:=a[i];
     end;
     fillchar(e,sizeof(e),0);
     fillchar(c,sizeof(c),0);
     min:=0;
     for k:=1 to m do
     begin
       readln(i,j);
       if not e[i,j] then
       begin
         e[i,j]:=true;
         e[j,i]:=true;
         inc(c[i,a[j]]);
         inc(c[j,a[i]]);
         min:=min+abs(a[i]-a[j])
       end;
     end;
     m:=0;
     result:=maxlongint;
     bool:=true;
     while m<1000 do
     begin
       if min<result then result:=min;
       inc(m);
       bool:=not bool;
       if not bool then
       for i:=1 to n do
         if b[i]=0 then
         begin
           if a[i]=0 then k:=1
           else k:=-1;
           if k-c[i,1]+c[i,0]<0 then
           begin
             bool:=true;
             min:=min+k-c[i,1]+c[i,0];
             b[i]:=1;
             for j:=1 to n do
             if e[i,j] then
             begin
               inc(c[j,1]);
               dec(c[j,0]);
             end;
           end
         end
         else
         begin
           if a[i]=1 then k:=1
           else k:=-1;
           if k-c[i,0]+c[i,1]<0 then
           begin
             bool:=true;
             min:=min+k-c[i,0]+c[i,1];
             b[i]:=0;
             for j:=1 to n do
             if e[i,j] then
             begin
               inc(c[j,0]);
               dec(c[j,1]);
             end;
           end
         end;
       if not bool then
       begin
         bool:=true;
         i:=random(n)+1;
         if b[i]=0 then
         begin
           if a[i]=0 then k:=1
           else k:=-1;
           min:=min+k-c[i,1]+c[i,0];
           b[i]:=1;
           for j:=1 to n do
           if e[i,j] then
           begin
             inc(c[j,1]);
             dec(c[j,0]);
           end;
         end
         else
         begin
           if a[i]=1 then k:=1
           else k:=-1;
           min:=min+k-c[i,0]+c[i,1];
           b[i]:=0;
           for j:=1 to n do
           if e[i,j] then
           begin
             inc(c[j,0]);
             dec(c[j,1]);
           end;
         end;
       end;
     end;
     writeln(result);
     close(input);
     close(output);
end.
