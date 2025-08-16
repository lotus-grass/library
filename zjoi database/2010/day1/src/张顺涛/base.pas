const leaves=32768;
var
  h,i,j,k,n,ans:longint;
  a,b,c,d,p,s,w:array[0..22222]of longint;
  tree,tmp:array[0..66666]of record min,del:longint;end;
function min(a,b:longint):longint;
  begin if a<b then exit(a);exit(b);end;
function find1(l,r,x:longint):longint;
  begin
    if l=r then exit(l);
    if d[(l+r)shr 1]>=x then exit(find1(l,(l+r)shr 1,x)) else exit(find1((l+r)shr 1+1,r,x));
  end;
function find2(l,r,x:longint):longint;
  begin
    if l=r then exit(l);
    if d[(l+r)shr 1+1]<=x then exit(find2((l+r)shr 1+1,r,x)) else exit(find2(l,(l+r)shr 1,x));
  end;
procedure qsort(l,r:longint);
  var ii,jj,tmp,mid:longint;
  begin
    ii:=l;jj:=r;mid:=b[(l+r)shr 1];
    repeat
      while b[ii]<mid do inc(ii);
      while b[jj]>mid do dec(jj);
      if ii<=jj then
        begin
          tmp:=b[ii];b[ii]:=b[jj];b[jj]:=tmp;
          tmp:=p[ii];p[ii]:=p[jj];p[jj]:=tmp;
          inc(ii);dec(jj);
        end;
    until ii>jj;
    if l<jj then qsort(l,jj);
    if ii<r then qsort(ii,r);
  end;
procedure ins(node,l,r:longint);
  begin
    if r<a[p[h]] then begin inc(tree[node].del,w[p[h]]);exit;end;
    ins(node shl 1,l,(l+r) shr 1);
    if (l+r) shr 1+1<a[p[h]] then ins(node shl 1+1,(l+r)shr 1+1,r);
    tree[node].min:=min(tree[node shl 1].min+tree[node shl 1].del,tree[node shl 1+1].min+tree[node shl 1+1].del);
  end;
function ask(node,l,r:longint):longint;
  var temp:longint;
  begin
    if r<j then exit(tree[node].min+tree[node].del);
    ask:=ask(node shl 1,l,(l+r)shr 1);
    if (l+r)shr 1+1<j then temp:=ask(node shl 1+1,(l+r)shr 1+1,r) else temp:=maxlongint;
    if ask>temp then ask:=temp;ask:=ask+tree[node].del;
  end;
begin
  assign(input,'base.in');
  assign(output,'base.out');
  reset(input);
  rewrite(output);
  readln(n,k);ans:=maxlongint;d[1]:=0;
  for i:=2 to n do read(d[i]);
  for i:=1 to n do read(c[i]);
  for i:=1 to n do read(s[i]);
  for i:=1 to n do read(w[i]);
  for i:=1 to n do a[i]:=find1(1,i,d[i]-s[i]);
  for i:=1 to n do b[i]:=find2(i,n,d[i]+s[i]);
  for i:=1 to n do p[i]:=i;qsort(1,n);
  inc(k);inc(n);a[n]:=n;b[n]:=n;c[n]:=0;p[n]:=n;
  fillchar(tree,sizeof(tree),0);
  for i:=leaves+1 to leaves+n do tree[i].min:=maxlongint shr 1;
  for i:=leaves-1 downto 1 do tree[i].min:=min(tree[i shl 1].min,tree[i shl 1+1].min);
  for i:=1 to k do
    begin
      fillchar(tmp,sizeof(tmp),0);h:=1;
      for j:=1 to n do
        begin
          while b[h]<j do begin ins(1,0,leaves-1);inc(h);end;  {a[p[h]]-1}
          tmp[j+leaves].min:=ask(1,0,leaves-1)+c[j];{j-1}
        end;
      if ans>tmp[n+leaves].min then ans:=tmp[n+leaves].min;
      tree:=tmp;
      for j:=leaves-1 downto 1 do
        tree[j].min:=min(tree[j shl 1].min,tree[j shl 1+1].min);
    end;
  writeln(ans);
  close(input);
  close(output);
end.
