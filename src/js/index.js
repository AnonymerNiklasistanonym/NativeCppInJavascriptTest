const {
    performance
} = require('perf_hooks');

const {
    count
} = require("./count")

const {
    helloUser
} = require("./greetings")

/**
 * @type {import("../typings/index")}
 */
const nativeModule = require("../../build/Release/greet.node")


const compareExecutionTime = (name, func1, func2, args) => {
    console.log(`> ${name}`)
    let time1 = 0
    let time2 = 0
    if (args !== undefined) {
        console.log(`>> Args: ${JSON.stringify(args)}`)

        const timeStart1 = performance.now();
        const result1 = func1(... args)
        const timeEnd1 = performance.now();
        console.log(result1)
        time1 = timeEnd1 - timeStart1
        console.log(`... ${time1} ms`)
        const timeStart2 = performance.now();
        const result2 = func2(... args)
        const timeEnd2 = performance.now();
        console.log(result2)
        time2 = timeEnd2 - timeStart2
        console.log(`... ${time2} ms`)
    } else {
        const timeStart1 = performance.now();
        const result1 = func1()
        const timeEnd1 = performance.now();
        console.log(result1)
        time1 = timeEnd1 - timeStart1
        console.log(`... ${time1} ms`)
        const timeStart2 = performance.now();
        const result2 = func2()
        const timeEnd2 = performance.now();
        console.log(result2)
        time2 = timeEnd2 - timeStart2
        console.log(`... ${time2} ms`)
    }
}

compareExecutionTime("helloUser [js vs native]", helloUser, nativeModule.helloUser)
compareExecutionTime("count [js vs native]", count, nativeModule.count, [1000000000])

try {
    nativeModule.count(undefined)
} catch (err) {
    console.log("Error was expected:", err)
}
try {
    nativeModule.count(null)
} catch (err) {
    console.log("Error was expected:", err)
}
