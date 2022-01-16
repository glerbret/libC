function GetAccessModifier(item) {
  access = 'public';
  Array.prototype.slice.call(item.getElementsByClassName('mlabel')).forEach(function(label) {
    if (label.innerText == 'private' || label.innerText == 'protected') { access = label.innerText; }
    label.className += ' '+label.innerText.replace(/ /g, '');
  });
  return access;
}

function DoAccessModifiers() {
  Array.prototype.slice.call(document.getElementsByClassName('memitem')).forEach(function(item) {
    var title = item.previousElementSibling;
    doc = item.getElementsByClassName('memdoc')[0];
    item = item.getElementsByClassName('memproto')[0];
    modifier = " "+GetAccessModifier(item);
    title.className += modifier;
    item.className += modifier;
    if(doc.childElementCount == 0) { item.className += ' empty'; doc.parentNode.removeChild(doc); }
  });
}
