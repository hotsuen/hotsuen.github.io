function number_word(){
    const ones = ["","one", "two","three","four","five","six","seven","eight","nine"];
    const teens = ["", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"];
    const tens = ["", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"];
    const thousands = ["", "thousand", "million", "billion"];

    if (num === 0) return "zero";

    let words = "";

    function helper(num, index){
        if (num === 0) return "";

        if (num < 10){
            return ones[num] + " ";
        }else if (num < 20){
            return teens[num - 10] + " ";
        }else if (num < 100){
            return tens[Math.floor(num /10)] + " " + ones[num % 10] + " ";
        }else {
            return ones[Math.floor(num / 100)] + " hundred " + helper(num % 100, 0);
        }
    }
    let i = 0;
    while (num > 0){
        let tempNum = num % 1000;
        if (tempNum !== 0){
            words = helper(tempNum, i) + thousands[i] + " " + words;
        }
        num = Math.floor(num / 1000);
        i++;
    }
    return words.trim();
}

function convertNumber(){
    let num = document.getElementById("numberInput").value;
    let result = numberToWords(parseInt(num));
    document.getElementById("result").textContent = result;
}