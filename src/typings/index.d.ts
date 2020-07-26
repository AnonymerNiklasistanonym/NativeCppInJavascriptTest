/**
 * greetHello function description
 */
declare function helloUser(): string;

/**
 * Count function description
 * @param num Number of times it should be counted
 */
declare function count(num: number): number;

interface CustomObjectOptions {
    string: string
    bool: bool
    number: number
    callback: (info: string) => void
}

declare class CustomObject {
    /**
     * Class constructor description
     * @param num Number
     * @param options Optional options
     */
    constructor(num: number, options?: CustomObjectOptions);
    /**
     * getValue function description
     */
    getValue(): number;
    /**
     * plusOne function description
     */
    plusOne(): number;
    /**
     * multiply function description
     */
    multiply(factor: number = 1.0): number;
    /**
     * runCallback function description
     */
    runCallback(): void;
}

export {
    count,
    CustomObject,
    helloUser
};
