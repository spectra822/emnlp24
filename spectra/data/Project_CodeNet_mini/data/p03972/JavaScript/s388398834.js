"use strict";
var input=require("fs").readFileSync("/dev/stdin","utf8");
var cin=input.split(/ |\n/),cid=0;
function next(){return +cin[cid++];}
function nextstr(){return cin[cid++];}
function nextbig(){return BigInt(cin[cid++]);}
function nexts(n,a){return a?cin.slice(cid,cid+=n):cin.slice(cid,cid+=n).map(a=>+a);}
function nextm(h,w,a){var r=[],i=0;if(a)for(;i<h;i++)r.push(cin.slice(cid,cid+=w));else for(;i<h;i++)r.push(cin.slice(cid,cid+=w).map(a=>+a));return r;}
function xArray(v){var a=arguments,l=a.length,r="Array(a["+--l+"]).fill().map(x=>{return "+v+";})";while(--l)r="Array(a["+l+"]).fill().map(x=>"+r+")";return eval(r);}

var myOut = main();
if(myOut !== undefined)console.log(String(myOut));

function main(){
  var w = next(), h = next();
  var a = [];
  for(var i = 0; i < w; i++){
    a.push([next(),0]);
  }
  for(var i = 0; i < h; i++){
    a.push([next(),1]);
  }
  a.sort((a,b)=>a[0]-b[0]);
  var ans = 0n;
  var x = 0, y = 0;
  for(var i = 0; i < h+w; i++){
    if(a[i][1] === 0){
      ans += BigInt(h-y+1) * BigInt(a[i][0]);
      x++;
    }else{
      ans += BigInt(w-x+1) * BigInt(a[i][0]);
      y++;
    }
  }
  return ans;
}