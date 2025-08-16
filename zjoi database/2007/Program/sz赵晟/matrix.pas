const inf='matrix.in';
      ouf='matrix.out';
      maxn=200;

var nn,n,nt,na,nb,pre,now:longint;
    ok:boolean;
    ima:array[1..maxn,1..maxn] of longint;
    cona,conb,fa:array[1..maxn] of longint;
    list:array[0..1,1..maxn*maxn] of longint;
    used:array[1..maxn] of boolean;
procedure setup;
begin
     assign(input,inf);
     reset(input);
     assign(output,ouf);
     rewrite(output);
end;

procedure endit;
begin
     close(input);
     close(output);
end;

procedure init;
var i,j:longint;
begin
     readln(n);
     for i:=1 to n do
        for j:=1 to n do
           read(ima[i][j]);
     fillchar(cona,sizeof(cona),0);
     fillchar(conb,sizeof(conb),0);
end;

procedure nk(na,nb,i:longint);
begin
     if na<>i then nk(fa[na],cona[na],i);
     cona[na]:=nb;conb[nb]:=na;
end;

procedure work;
var i,j,k:longint;
begin
     for i:=1 to n do
        for j:=1 to n do
        if (conb[j]=0) and (ima[i][j]=1) then
        begin
             cona[i]:=j;
             conb[j]:=i;
             break;
        end;
    while true do
    begin
         ok:=true;
         for i:=1 to n do if cona[i]=0 then begin ok:=false;break;end;
         if ok then begin writeln('Yes');exit; end;
         for i:=1 to n do if cona[i]=0 then
         begin
              nt:=0;now:=1;ok:=false;
              while (now<>0) and (ok=false) do
              begin
                   pre:=now;now:=0;nt:=1-nt;list[0][1]:=i;fillchar(used,sizeof(used),0);
                   for j:=1 to pre do
                   begin
                        na:=list[1-nt][j];
                        for k:=1 to n do
                        if (ima[na][k]=1) and (k<>cona[na]) then
                        begin
                             if conb[k]=0 then begin ok:=true;nb:=k;break;end;
                             if used[k] then continue;
                             used[k]:=true;
                             fa[conb[k]]:=na;
                             inc(now);
                             list[nt][now]:=conb[k];
                        end;
                        if ok then
                        begin
                             nk(na,nb,i);
                             break;
                        end;
                   end;
              end;
              if ok then break;
              writeln('No');
              exit;
         end;
    end;
end;

begin
  setup;
     readln(nn);
     while (nn>0) do
     begin
          dec(nn);
          init;
          work;
     end;
  endit;
end.
