var
  i,k,m,n,x,y,c,w,tot,ans1,ans2:longint;
  e:array[0..55555]of record x,y,c,w,z,next:longint;end;
  d,first,now:array[0..1111]of longint;
  v:array[0..1111]of boolean;
function min(a,b:longint):longint;
  begin if a<b then exit(a);exit(b);end;
procedure addedge(x,y,c,w,z:longint);
  begin
    inc(tot);e[tot].x:=x;e[tot].y:=y;e[tot].c:=c;e[tot].w:=w;
    e[tot].z:=z+tot;e[tot].next:=first[x];first[x]:=tot;
  end;
function aug(x,flow:longint):longint;
  var num,y,tmp:longint;
  begin
    if x=n then begin ans1:=ans1+flow;ans2:=ans2+flow*d[1];exit(flow);end;
    num:=now[x];v[x]:=true;
    while num>0 do
      begin
        y:=e[num].y;
        if (e[num].c>0)and not v[y] and(d[x]=d[y]+e[num].w) then
          begin
            tmp:=aug(y,min(flow,e[num].c));
            if tmp>0 then
              begin
                dec(e[num].c,tmp);
                inc(e[e[num].z].c,tmp);
                now[x]:=num;
                exit(tmp);
              end;
          end;
        num:=e[num].next;
      end;
    now[x]:=0;
    exit(0);
  end;
function modlable:boolean;
  var num,y,tmp:longint;
  begin
    tmp:=maxlongint;
    for i:=1 to n do if v[i] then
      begin
        num:=first[i];
        while num>0 do
          begin
            y:=e[num].y;
            if (e[num].c>0)and not v[y] and(tmp>d[y]+e[num].w-d[i]) then
              tmp:=d[y]+e[num].w-d[i];
            num:=e[num].next;
          end;
      end;
    if tmp=maxlongint then exit(true);
    for i:=1 to n do if v[i] then
      begin inc(d[i],tmp);v[i]:=false;end;
    exit(false);
  end;
begin
  assign(input,'network.in');
  assign(output,'network.out');
  reset(input);
  rewrite(output);
  readln(n,m,k);tot:=0;
  fillchar(first,sizeof(first),0);
  for i:=1 to m do
    begin
      readln(x,y,c,w);
      addedge(x,y,c,w,1);
      addedge(y,x,0,-w,-1);
    end;
  fillchar(d,sizeof(d),0);ans1:=0;
  repeat
    for i:=1 to n do now[i]:=first[i];
    repeat fillchar(v,sizeof(v),false);until aug(1,maxlongint)=0;
  until modlable;
  write(ans1,' ');
  for i:=1 to n do
    begin
      m:=first[i];
      while m>0 do
        begin
          if odd(m) then
            begin
              addedge(e[m].x,e[m].y,k,e[m].w,1);
              addedge(e[m].y,e[m].x,0,-e[m].w,-1);
              e[m].w:=0;e[m+1].w:=0;
            end;
          m:=e[m].next;
        end;
    end;
  inc(n);addedge(n-1,n,k,0,1);addedge(n,n-1,0,0,-1);
  fillchar(d,sizeof(d),0);ans2:=0;
  repeat
    for i:=1 to n do now[i]:=first[i];
    repeat fillchar(v,sizeof(v),false);until aug(1,maxlongint)=0;
  until modlable;
  writeln(ans2);
  close(input);
  close(output);
end.
