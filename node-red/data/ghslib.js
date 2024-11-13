// ghslib.js

module.exports.hello = function() {
    return "Hello from the ghslib.js";
};

module.exports.formatTime = function(hour, minute) {
    return `${hour.toString().padStart(2, '0')}:${minute.toString().padStart(2, '0')}`;
}

/**
 * Checks if a specific time falls within a specified time range.
 * 
 * @param {Date} dateTime - The date and time to check.
 * @param {number} fromHour - The starting hour of the range.
 * @param {number} fromMinute - The starting minute of the range.
 * @param {number} toHour - The ending hour of the range.
 * @param {number} toMinute - The ending minute of the range.
 * @param {boolean} [debug=false] - Optional parameter. If set to true, outputs debug information.
 * @param {Object} [node=undefined] - Optional Node-RED node object parameter. When called from a Node-RED function node, 
 *                                     could be used to pass the function node object, allowing to use node's methods.
 * 
 * The function correctly interprets the given range even if the same hour is used for the starting and ending hour, 
 * and the starting minute is later than the ending minute. In this case, the range spans over midnight. For instance, 
 * a range from 22:30 to 22:20 will span from 22:30 on one day to 22:20 on the next.
 *
 * @returns {boolean} True if the time falls within the range, false otherwise.
 *
 * @example
 * 
 * // Regular JavaScript environment usage
 * let dateInstance = new Date();
 * let isInRange = isTimeInRange(dateInstance, 9, 30, 17, 30, true);
 *
 * // Node-RED function node usage
 * let dateInstance = new Date();
 * let isInRange = isTimeInRange(dateInstance, 9, 30, 17, 30, true, node);
 */

module.exports.isTimeInRange = function(dateTime, fromHour, fromMinute, toHour, toMinute, debug = false, node = undefined) {

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

    // If targetTime is before startTime, adjust targetTime to 'next day' for correct comparison due to crossing over midnight.
    if(targetTime < startTime) {
        targetTime.setDate(targetTime.getDate() + 1);
    }

    var isInRange = targetTime >= startTime && targetTime <= endTime;
    
    if(debug) {
        const logMessage = "Time From: " + module.exports.formatTime(startTime.getHours(), startTime.getMinutes()) +
                           ", Time To: " + module.exports.formatTime(endTime.getHours(), endTime.getMinutes()) +
                           ", Testing Time: " + module.exports.formatTime(targetTime.getHours(), targetTime.getMinutes()) +
                           ", In Range: " + isInRange;
        // prints debug info based on the node object
        if (node && typeof node.warn === 'function') {
            node.warn(logMessage);
        } else {
            console.log(logMessage);
        }
    }

    // Check if targetTime is within or equal to the start and end times.
    return isInRange;
};




module.exports.getNightTimeObject = function(dateTime) {
    return {
        fromHour: 1,
        fromMinute: 0,
        toHour: 7,
        toMinute: 50
    };
};

module.exports.isNightTime = function(dateTime, debug = false, context = undefined) {
    //01:00 - 07:50 is night time
    let nightTime = module.exports.getNightTimeObject(dateTime);
    return module.exports.isTimeInRange(dateTime, nightTime.fromHour, nightTime.fromMinute, nightTime.toHour, nightTime.toMinute, debug, context);
};
