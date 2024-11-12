// {"motion":"false","timestamp":"2024-11-06T09:20:09.123Z"}


msg =
{
    "topic": "bathroomMotion/motion",
    "payload": {
        "motion": "true",
        "timestamp": "2024-11-07T09:05:32.996Z"
    },
    "qos": 0,
    "retain": false,
    "_msgid": "dd3b8a1e90a383e5"
}

msg =
{
    "topic": "bathroomMotion/motion",
    "payload": {
        "motion": "false",
        "timestamp": "2024-11-12T09:18:49.820Z"
    },
    "qos": 0,
    "retain": false,
    "_msgid": "144892ec108c1561"
}

// msg =
// {
//     "topic": "bathroomMotion/illuminance",
//     "payload": {
//         "Illuminance": "0",
//         "timestamp": "2024-11-07T09:06:32.622Z"
//     },
//     "qos": 0,
//     "retain": false,
//     "_msgid": "af2fb579b18c46b0"
// }

function greet() {
  console.log('Hello, World!');
  console.log(JSON.stringify(msg, null, 3));
}

function getDateTime(jsonMsg) {
  //convert timestamp to date time and return it
    var dateTime = new Date(jsonMsg.payload.timestamp);
    return dateTime;
}

/**
 * Checks if a specific time falls within a specified time range.
 * 
 * @param {Date} dateTime - The date and time to check.
 * @param {number} fromHour - The starting hour of the range.
 * @param {number} fromMinute - The starting minute of the range.
 * @param {number} toHour - The ending hour of the range.
 * @param {number} toMinute - The ending minute of the range.
 * 
 * The function correctly interprets the given range even if the same hour is used for the starting and ending hour, 
 * and the starting minute is later than the ending minute. In this case, the range spans over midnight. For instance, 
 * a range from 22:30 to 22:20 will span from 22:30 on one day to 22:20 on the next.
 *
 * @returns {boolean} True if the time falls within the range, false otherwise.
 */
function isTimeInRange(dateTime, fromHour, fromMinute, toHour, toMinute) {
    var targetTime = new Date(dateTime);

    var startTime = new Date(dateTime);
    startTime.setHours(fromHour);
    startTime.setMinutes(fromMinute);
    startTime.setSeconds(0);
    startTime.setMilliseconds(0);

    var endTime = new Date(startTime);
    // If fromHour > toHour, the span crosses over midnight.
    if(fromHour > toHour || (fromHour === toHour && fromMinute > toMinute)) {
        endTime.setDate(endTime.getDate() + 1); // Set endTime as 'next day', as the span crosses midnight.
    }
    endTime.setHours(toHour);
    endTime.setMinutes(toMinute);
    endTime.setSeconds(59);
    endTime.setMilliseconds(999);

    // If targetTime is before startTime, adjust targetTime to 'next day' for correct comparison (due to crossing over midnight).
    if(targetTime < startTime) {
        targetTime.setDate(targetTime.getDate() + 1);
    }

    // Check if targetTime is within or equal to the start and end times.
    return targetTime >= startTime && targetTime <= endTime;
}

///////////////////////
msg.payload.timestamp = "2024-11-07T09:05:32.996Z";
msg.payload.timestamp = "2024-11-12T06:59:21.494Z";
msg.payload.timestamp = "2024-11-12T22:59:21.494Z";
console.log("Timestamp: " + getDateTime(msg));

// greet();

let fromHour = 23, fromMinute = 0, toHour = 8, toMinute = 10;
let fromStr = formatTime(fromHour, fromMinute);
let toStr = formatTime(toHour, toMinute);

function formatTime(hour, minute) {
    return `${hour.toString().padStart(2, '0')}:${minute.toString().padStart(2, '0')}`;
}

function isNightTime(dateTime) {
    // Assuming night time is from 20 (8 PM) to 6 (6 AM)
    return isTimeInRange(dateTime, 23, 0, 7, 55);
}

// Test the isNightTime function by creating a Date object
var dateTime = new Date(msg.payload.timestamp);
console.log("Current time: " + dateTime);

if (isNightTime(dateTime)) {
    console.log("It's \033[01;32mnight time\033[0m.");
} else {
    console.log("It's \033[01;31mday time\033[0m.");
}

console.log("Current time: " + formatTime(getDateTime(msg).getHours(), getDateTime(msg).getMinutes()));

if (isTimeInRange(getDateTime(msg), fromHour, fromMinute, toHour, toMinute)) {

    console.log("Motion detected in the bathroom \033[01;32mbetween\033[0m "+ fromStr + " and "+ toStr +".");
} else {
    console.log("Motion detected in the bathroom \033[01;31moutside\033[0m "+ fromStr + " and "+ toStr +".");
}


console.log("-------------------Tests for isTimeInRange function-------------------");


// Test 1
var msg = {payload: {timestamp: new Date("2022-01-01T23:00:00Z").getTime()}}; // DateTime is 23:00
console.log("Current time: " + getDateTime(msg));
if (isTimeInRange(getDateTime(msg), 23, 1, 7, 59)) {
    console.log("Motion detected in the bathroom \033[01;32mbetween\033[0m "+ fromStr + " and "+ toStr +".");
} else {
    console.log("Motion detected in the bathroom \033[01;31moutside\033[0m "+ fromStr + " and "+ toStr +".");
}


// Test 2
msg = {payload: {timestamp: new Date("2022-01-01T02:00:00Z").getTime()}}; // DateTime is 02:00
console.log("Current time: " + getDateTime(msg));
if (isTimeInRange(getDateTime(msg), 1, 1, 7, 59)) {
    console.log("Motion detected in the bathroom \033[01;32mbetween\033[0m "+ fromStr + " and "+ toStr +".");
} else {
    console.log("Motion detected in the bathroom \033[01;31moutside\033[0m "+ fromStr + " and "+ toStr +".");
}

// Test 2
msg = {payload: {timestamp: new Date("2022-01-01T07:10:00Z").getTime()}}; // DateTime is 02:00
console.log("Current time: " + getDateTime(msg));
if (isTimeInRange(getDateTime(msg), 1, 1, 7, 59)) {
    console.log("Motion detected in the bathroom \033[01;32mbetween\033[0m "+ fromStr + " and "+ toStr +".");
} else {
    console.log("Motion detected in the bathroom \033[01;31moutside\033[0m "+ fromStr + " and "+ toStr +".");
}

// Test 4
msg = {payload: {timestamp: new Date("2022-01-01T04:00:00Z").getTime()}}; // the DateTime is 04:00
console.log("Current time: " + getDateTime(msg));
if (isTimeInRange(getDateTime(msg), 4, 1, 7, 59)) {
    console.log("Motion detected in the bathroom \033[01;32mbetween\033[0m "+ fromStr + " and "+ toStr +".");
} else {
    console.log("Motion detected in the bathroom \033[01;31moutside\033[0m "+ fromStr + " and "+ toStr +".");
}
