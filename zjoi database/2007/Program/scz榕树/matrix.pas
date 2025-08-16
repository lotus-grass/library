const maxn=402;

var m,n,s,t:longint;
    c,f:array[1..maxn,1..maxn]of longint;
    q,vf,fa:array[1..maxn]of longint;

procedure prepare;
var temp,i,j:longint;
begin
     readln(n);
     fillchar(c,sizeof(c),0);
     for i:=1 to n do
       for j:=1 to n do read(c[i,j+n]);
     s:=n*2+1;
     t:=n*2+2;
     for i:=1 to n do
     begin
       c[s,i]:=1;
       c[i+n,t]:=1;
     end;
end;

function find_path:boolean;
var i,j,u,v:longint;
begin
     i:=1;
     j:=1;
     q[1]:=s;
     vf[s]:=maxlongint;
     fa[s]:=s;
     fillchar(fa,sizeof(fa),0);
     while i<=j do
     begin
       u:=q[i];
       for v:=1 to t do
       if (fa[v]=0)and(c[u,v]-f[u,v]>0) then
       begin
         inc(j);
         q[j]:=v;
         fa[v]:=u;
         if c[u,v]-f[u,v]<vf[u] then vf[v]:=c[u,v]-f[u,v]
         else vf[v]:=vf[u];
         if v=t then exit(true);
       end;
       inc(i);
     end;
     exit(false)
end;

procedure work;
var i,sum:longint;
begin
     fillchar(f,sizeof(f),0);
     sum:=0;
     while find_path do
     begin
       i:=t;
       sum:=sum+vf[t];
       while i<>s do
       begin
         inc(f[fa[i],i],vf[t]);
         dec(f[i,fa[i]],vf[t]);
         i:=fa[i];
       end;
     end;
     if sum=n then writeln('Yes')
     else writeln('No')
end;

begin
     assign(input,'matrix.in');
     reset(input);
     assign(output,'matrix.out');
     rewrite(output);
     readln(m);
     while m>0 do
     begin
       dec(m);
       prepare;
       work;
     end;
     close(input);
     close(output);
end.
