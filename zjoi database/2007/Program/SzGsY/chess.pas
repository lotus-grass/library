const
     max=2000;
var
   n,m,ans1,ans2:longint;
   a:array[0..max,0..max] of 0..1;
   up,left:array[0..max,0..max] of longint;
   lie,hang:array[0..max,0..max] of longint;
procedure setup;
begin
     assign(input,'chess.in');
     assign(output,'chess.out');
     reset(input);
     rewrite(output);
end;
procedure closeit;
begin
     close(input);
     close(output);
end;
procedure init;
var
   i,j:longint;
begin
     readln(n,m);
     for i:=1 to n do for j:=1 to m do read(a[i,j]);
end;
procedure prefix;
var
   i,j:longint;
begin
   {up}
     for j:=1 to m do
     begin
          for i:=1 to n do
            if i=1 then up[i,j]:=1
                   else if a[i,j]+a[i-1,j]=1 then up[i,j]:=up[i-1,j]
                   else up[i,j]:=i;
     end;
    {left}
    for i:=1 to n do
    begin
         for j:=1 to m do
          if j=1 then left[i,j]:=1
                 else if a[i,j]+a[i,j-1]=1 then left[i,j]:=left[i,j-1]
                 else left[i,j]:=j;
    end;
end;
procedure work;
var
   i,j:longint;
begin
     for i:=1 to n do
      for j:=1 to m do
     begin
        if i=1 then lie[i,j]:=1
               else
        begin
             lie[i,j]:=lie[i,j-1];
             if lie[i,j]<up[i,j] then lie[i,j]:=up[i,j];
        end;
        if j=1 then hang[i,j]:=1
               else
        begin
             hang[i,j]:=hang[i-1,j];
             if hang[i,j]<left[i,j] then hang[i,j]:=left[i,j];
        end;
     end;
end;
function min(a,b:longint):longint;
begin
    if a>b then exit(b)
           else exit(a);
end;
procedure print;
var
   i,j,bian:longint;
begin
      ans1:=-maxlongint;
      ans2:=-maxlongint;
      for i:=1 to n do
        for j:=1 to m do
      begin
           if (j-hang[i,j]+1)*(i-lie[i,j]+1)>ans1 then ans1:=(j-hang[i,j]+1)*(i-lie[i,j]+1);
           bian:=min((j-hang[i,j]+1),(i-lie[i,j]+1));
           if bian*bian>ans2 then ans2:=bian*bian;
      end;
      writeln(ans2);
      writeln(ans1);
end;
begin
     setup;
     init;
     prefix;
     work;
     print;
     closeit;
end.
