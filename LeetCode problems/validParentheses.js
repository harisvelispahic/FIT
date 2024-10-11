/**
 * @param {string} s
 * @return {boolean}
 */
var isValid = function (s) {
  if (s.length === 0) return true;
  let buffer = [];
  buffer.push(s[0]);

  for (let i = 1; i < s.length; i++) {
    if (s[i] === ")") {
      if (buffer[buffer.length - 1] === "(") {
        buffer.pop();
      } else {
        buffer.push(s[i]);
      }
    } else if (s[i] === "]") {
      if (buffer[buffer.length - 1] === "[") {
        buffer.pop();
      } else {
        buffer.push(s[i]);
      }
    } else if (s[i] === "}") {
      if (buffer[buffer.length - 1] === "{") {
        buffer.pop();
      } else {
        buffer.push(s[i]);
      }
    } else {
      buffer.push(s[i]);
    }
  }
  return buffer.length === 0;
};
