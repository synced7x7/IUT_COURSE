**Batch 20 MAD Quiz 1 — Q1**

When flexDirection is `'column'`, the main axis runs vertically and the cross axis runs horizontally. In the figure, the three boxes stack from the top downward with no spacing between them, so `justifyContent: 'flex-start'` (items begin at the top of the container along the main axis). The boxes are left-aligned rather than centered or stretched, so `alignItems: 'flex-start'` (items sit at the start of the cross axis, i.e., the left edge).

---

**Batch 20 MAD Quiz 1 — Q2**

**1. Asynchronous Programming** — A style of programming where operations are initiated and allowed to complete in the background without blocking subsequent code execution. The program does not wait for the operation to finish before moving to the next line.

Example:
```javascript
const fetchData = async () => {
  const response = await fetch('https://api.example.com/data');
  const data = await response.json();
  console.log(data);
};
console.log('This runs before fetchData finishes');
fetchData();
```

**2. Setup function of useEffect** — The setup function is the callback passed as the first argument to `useEffect`. It contains the side-effect logic to run after the component renders. It can optionally return a cleanup function.

Example:
```javascript
useEffect(() => {
  // Setup: subscribe to something
  const sub = DataSource.subscribe(handleData);
  // Cleanup (returned function):
  return () => DataSource.unsubscribe(sub);
}, []);
```

**3. Conditional Rendering** — Rendering different UI elements or components based on a condition, so the output changes depending on state, props, or any boolean expression.

Example:
```javascript
const App = () => {
  const isLoggedIn = true;
  return (
    <View>
      {isLoggedIn ? <Text>Welcome back!</Text> : <Text>Please log in</Text>}
    </View>
  );
};
```

---

**Batch 20 MAD Quiz 1 — Q3**

Children communicate with parents using a callback function passed down as a prop. The five steps are:

Step 1 — The parent defines a callback function that contains the logic it wants to execute when the child has something to communicate.

Step 2 — The parent passes this callback function to the child as a prop, e.g., `<Child onDataSend={handleDataFromChild} />`.

Step 3 — The child receives the prop in its function parameters, e.g., `const Child = ({ onDataSend }) => { ... }`.

Step 4 — When an event occurs in the child (such as a button press), the child calls the received prop function and passes data as an argument, e.g., `onDataSend('hello from child')`.

Step 5 — The parent's callback executes with the data, and the parent can update its own state accordingly (e.g., `setMessage(data)`), causing a re-render with the new information from the child.

---

**Batch 20 MAD Quiz 1 — Q4**

**4.1)** The ternary expression `(age >= 18) ? 1 : 2` evaluates to `2` when the condition is false. Therefore, division equals 2 when `age < 18`. The range of age is **age < 18** (i.e., age is 17 or below, or any value less than 18).

**4.2)** The switch operates on `true` and matches the first case whose expression evaluates to `true`.

For **id = 6**:
- `id%2===0` → `6%2=0` → `true` → logs `'id is even'`, then hits `break`. Output: **"id is even"**

For **id = 9**:
- `id%2===0` → `9%2=1` → `false`, skip
- `id%3===0` → `9%3=0` → `true` → logs `'id is multiple of 3'`
- There is **no break** after this case, so execution falls through to the next case
- `id%2!==0` → `9%2=1!==0` → `true` → logs `'id is odd'`, then hits `break`
- Output: **"id is multiple of 3"** then **"id is odd"**

The key difference is that id=6 hits a break immediately and only produces one output, while id=9 falls through from the multiple-of-3 case into the odd case, producing two outputs due to the missing break.

**4.3)** The problem is the **missing cleanup function**. The line `return () => clearInterval(timer)` is commented out. The `useEffect` has `[timers]` as its dependency array, meaning it re-runs every time `timers` changes. Since `setTimers` is called inside the interval callback, `timers` changes on every tick, which triggers the effect again, creating a new `setInterval` without clearing the previous one. This causes exponentially growing intervals all running simultaneously, leading to memory leaks and increasingly rapid state updates that spiral out of control. The fix is to uncomment the cleanup return so each old interval is cleared before a new one starts.

**4.4)** The `?????` values to swap in:

In the props destructuring: `onRemove` (the missing prop between `onEditFormOpen` and `onToggleRunning`)

In the JSX:
- `{elapsedString}` for the elapsed time Text display
- `"Edit"` for the blue TimerButton title
- `"red"` (or appropriate color string) for the Remove button's color prop
- `"Stop"` for the running state title (the expression is `isRunning ? "Stop" : "Start"`)

---

**Batch 20 MAD Quiz 1 — Q5**

**5.1) State criteria** — A piece of data should be stored in state if it meets all of the following: it changes over time in response to user interaction or external events; its change must cause the component to re-render to reflect the updated UI; it cannot be computed or derived from existing props or other state variables; and it is not passed in from a parent as a prop. If any of these conditions are not met, the data should not be state.

**5.2) Difference between state and prop**

State is owned and managed internally by the component. The component itself can change its state using the setter function (e.g., `setState`). State changes trigger a re-render of the component. Props, on the other hand, are read-only values passed down from a parent component. The child cannot modify its own props. While both cause re-renders when they change, only the parent can change a prop by passing a new value. State is local and private; props are the communication channel from parent to child.

**5.3) Output:**
```javascript
const names = ['atiq','shafin','rahman','edon','jafrin','alin']
console.log(names.filter((nm) => nm.length >= 6))
```
Lengths: atiq=4, shafin=6, rahman=6, edon=4, jafrin=6, alin=4

Output: `['shafin', 'rahman', 'jafrin']`

**5.4) VAR vs LET**

`var` is **function-scoped** — it is accessible anywhere within the function in which it is declared, even before the declaration line (it is hoisted and initialized as `undefined`). It can also be re-declared in the same scope without error.

`let` is **block-scoped** — it is only accessible within the `{}` block in which it is declared. It is hoisted but not initialized (it sits in the Temporal Dead Zone until the declaration line), so accessing it before declaration throws a ReferenceError. It cannot be re-declared in the same scope.

Stack procedure visualization:
```
// VAR — function scope stack
function test() {
  // [var x = undefined] ← hoisted to function stack at call time
  console.log(x); // undefined (no error)
  var x = 5;
  if (true) {
    var x = 10; // same x in function stack, overwrites it
  }
  console.log(x); // 10 — var leaks out of the if-block
}

// LET — block scope stack
function test() {
  // let y in TDZ — not accessible yet
  let y = 5; // pushed onto function block's stack
  if (true) {
    // new block pushed onto stack
    let y = 10; // different y, pushed onto if-block's stack
    console.log(y); // 10
    // if-block ends → y=10 popped off stack
  }
  console.log(y); // 5 — original y still on function block's stack
}
```

---

**Batch 20 MAD Quiz 2 — Q1**

If a component doesn't show up, check the following: First, verify the component has explicit `width` and `height` in its style, or that its parent has `flex: 1` — a component with no dimensions and no flex context collapses to zero size and renders invisibly. Second, check if the component or any ancestor has `display: 'none'` or `opacity: 0`. Third, confirm there is no conditional rendering logic (such as a state flag) that evaluates to `false`, suppressing the component. Fourth, temporarily add a `backgroundColor` to the component's style to see if the space exists but content is invisible.

---

**Batch 20 MAD Quiz 2 — Q2**

A scenario where dynamic style is needed: a toggle button that switches between an active and inactive state. When the user taps it, the background color should change from gray (inactive) to blue (active). The style object is computed based on a boolean state variable:
```javascript
const [active, setActive] = useState(false);
<TouchableOpacity style={[styles.btn, active && styles.activeBtn]} onPress={() => setActive(!active)} />
```
Here the style applied changes dynamically at runtime based on the `active` state.

---

**Batch 20 MAD Quiz 2 — Q3**

`Text` is specifically for rendering textual content and supports text-specific props like `numberOfLines`, `ellipsizeMode`, and nested inline text styling. `View` is a generic layout container that cannot render text directly and is used purely for grouping and positioning child components using flexbox.

---

**Batch 20 MAD Quiz 2 — Q4**

`numberOfLines` — limits the rendered text to a specified number of lines, truncating the overflow with an ellipsis. Example: `<Text numberOfLines={2}>Long string...</Text>`.

---

**Batch 20 MAD Quiz 2 — Q5**

Both `TouchableOpacity` and `TouchableHighlight` require wrapping their children in an extra native View layer, which adds unintended nesting to the component hierarchy and can interfere with flexbox layouts in certain configurations. A more specific individual inconvenience: `TouchableHighlight` requires exactly one child element — passing zero or more than one child throws an error.

---

**Batch 20 MAD Quiz 2 — Q6**

The `margin: 50` sets all margins to 50, but `marginTop: 22` and `marginBottom: 40` override those sides. `padding: 17` sets all padding, but `paddingRight: 67` overrides the right. `border: 10` sets all borders, but `borderTop: 18` overrides the top border.

Resolved values:
- paddingLeft=17, paddingRight=67, paddingTop=17, paddingBottom=17
- borderLeft=10, borderRight=10, borderTop=18, borderBottom=10
- marginLeft=50, marginRight=50, marginTop=22, marginBottom=40

Rendered width of the View (content + padding + border):
1718 + 17 + 67 + 10 + 10 = **1822**

Rendered height of the View (content + padding + border):
123 + 17 + 17 + 18 + 10 = **185**

Total space occupied including margins: width = 1822 + 50 + 50 = 1922, height = 185 + 22 + 40 = 247.

---

**Batch 20 MAD Quiz 2 — Q7**

**Process 1 — Local image using require():**
```javascript
import { Image } from 'react-native';

<Image
  source={require('./assets/photo.png')}
  style={{ width: 200, height: 200 }}
/>
```
The image is bundled with the app and loaded from the local filesystem.

**Process 2 — Remote image using a URI:**
```javascript
<Image
  source={{ uri: 'https://example.com/image.jpg' }}
  style={{ width: 200, height: 200 }}
/>
```
The image is fetched from the network at runtime. Width and height must be explicitly set because RN cannot infer remote image dimensions automatically.

---

**Batch 20 MAD Quiz 2 — Q8**

`aspectRatio: 2` means the width of the Image component will be exactly twice its height (a 2:1 ratio). If the height is constrained to 100, the width will automatically be set to 200. It allows one dimension to be defined while the other scales proportionally to maintain the ratio.

---

**Batch 20 MAD Quiz 2 — Q9**

```javascript
<View style={{
  width: 100,
  height: 100,
  borderRadius: 50,
  backgroundColor: 'blue'
}} />
```
Set equal `width` and `height`, then set `borderRadius` to exactly half of that value. This rounds all four corners to the same radius, producing a perfect circle.

---

**Batch 20 MAD Quiz 2 — Q10**

`flexDirection: 'row'` lays children out horizontally from left to right. The first child appears at the leftmost position and subsequent children follow to the right.

`flexDirection: 'row-reverse'` lays children out horizontally from right to left. The first child appears at the rightmost position and subsequent children are placed to its left.

```
row:         [A]  [B]  [C]   → left to right
row-reverse: [C]  [B]  [A]   → right to left
```
The visual order is reversed but the logical order in code remains unchanged.

---

**Batch 20 MAD Quiz 2 — Q11**

Opacity animation is smooth and low-latency because it runs entirely on the **native UI thread** rather than the JavaScript thread, when `useNativeDriver: true` is set. The Animated API serializes the animation configuration and hands it off to the native layer once. From that point, every frame update is computed and applied natively without any JS-to-native bridge calls per frame. Since the JS thread (which handles business logic, state updates, and React reconciliation) is never involved in the per-frame rendering, even a busy or blocked JS thread cannot cause dropped frames in the animation.

---

**Batch 20 MAD Mid — Code fill-in-the-blanks (Code Snippet 4)**

- Line 2: `'????'` → `'react'`
- Line 8: `????` → `useEffect`
- Line 29: `????` (before `: {es}`) → `Total Expense`
- Line 31: `</????>` → `</View>`
- Line 34: `export default ????` → `CalculateExpense`

**Batch 20 MAD Mid — Q3(c)** — Same answers as Batch 20 MAD Quiz 1 Q2 above (Asynchronous Programming, Setup function of useEffect, Conditional Rendering).

---

**Batch 20 MAD Quiz 3 — Q1**

**Practice 1 — Minimal and focused input fields**
Only show the fields that are absolutely necessary for sign-in: an email/username field and a password field. Do not add extra fields like date of birth, phone number, or CAPTCHA on the sign-in screen. Every additional field increases abandonment. Illustration: a clean screen with two input fields, a "Sign In" button, a "Forgot Password" link, and nothing else.

**Practice 2 — Clear, specific error messages**
When credentials are wrong, show an inline error message directly below the relevant field in red, such as "Incorrect password" rather than a generic "Login failed" alert. This tells the user exactly what to correct. Illustration: the password field with a red border and a message beneath it reading "Your password is incorrect. Try again."

**Practice 3 — Password visibility toggle**
Add an eye icon inside the password input field. Tapping it toggles the text between hidden (dots) and visible characters. This reduces sign-in failures caused by typing errors the user cannot see. Illustration: a password field with a visible eye icon on the right edge.

**Practice 4 — Large, full-width primary action button**
The "Sign In" button should span the full width of the form or close to it, with sufficient vertical padding (at least 48dp height) so it is easy to tap on any screen size without misses. It should have strong visual contrast (e.g., filled background color) to stand out as the primary action. Illustration: a wide button clearly differentiated from secondary actions like "Forgot Password."

**Practice 5 — Support for OS auto-fill and biometric login**
The email and password fields should have appropriate `textContentType` and `autoComplete` attributes so the OS can suggest saved credentials. For returning users, offer biometric authentication (Face ID / fingerprint) as an alternative to re-typing credentials. Illustration: a "Sign in with Face ID" option appearing below the standard form for returning users.

---

**Batch 20 MAD Quiz 3 — Q2**

**Anti-pattern 1: Displaying user credentials to all users inside the booked room**
"Everyone using the app will get to see your credentials inside your booked room" is a critical privacy and security anti-pattern. User credentials (email and password) must never be exposed to other users under any circumstance.
Solution: After successful booking, only display non-sensitive identification (e.g., the user's name or student ID) alongside the booking details. Credentials must remain server-side and never be transmitted to or rendered on other users' screens.

**Anti-pattern 2: Requiring double confirmation of credentials during sign-in**
"You need to confirm them a second time and you are signed in" — asking users to re-enter both email and password to confirm during sign-in is an anti-pattern. Confirmation of credentials (typing them twice) belongs only in the sign-up/registration flow to prevent account creation errors. Applying it to sign-in adds unnecessary friction and slows down a flow users must complete every session.
Solution: During sign-in, collect credentials exactly once. Reserve the double-entry confirmation pattern strictly for the one-time registration screen.

---

**Batch 20 MAD Quiz 3 — Q3**

**Problem:** On web, horizontal progress bars with step labels work well because desktop screens are wide. On mobile, the limited horizontal viewport causes the same pattern to fail. A 5-step bar like `[Step1]─[Step2]─[Step3]─[Step4]─[Step5]` becomes illegible because each segment is too narrow, labels get truncated or overlap, and the current step is hard to distinguish. With more than 3–4 steps, the bar degrades into an unreadable strip.

```
Problem (mobile):
[Reg]─[Ver]─[Pro]─[Pay]─[Con]   ← unreadable, labels cut off
```

**Solution:** Replace the horizontal multi-segment bar with a "Step X of Y" text label combined with a single continuous progress bar showing overall completion percentage. This requires zero horizontal space for labels and always communicates position clearly regardless of how many steps exist.

```
Solution:
Step 2 of 5
[████████░░░░░░░░░░░░]  40%
```

Alternatively for flows with 3–5 steps, a dot indicator works well:
```
● ● ○ ○ ○   (filled = completed/current, empty = remaining)
```
Both approaches scale correctly to any screen width.

---

**Batch 20 MAD Quiz 3 — Q4**

**Challenge:** Limited horizontal screen width makes it impossible to display many columns simultaneously. Users must scroll horizontally to see all data, and once they do, they lose the row header context — they no longer know which row they are reading because the leftmost identifying column has scrolled off-screen.

**Opportunity:** The touchscreen interface enables interactive row expansion. Instead of cramming all data into a flat table, rows can be tapped to reveal a full detail view, effectively turning a wide table into a drill-down navigation pattern. This takes advantage of mobile's natural interaction model and allows far more information to be presented per item than any fixed-width table could accommodate.

---

**Batch 20 MAD Quiz 3 — Q5**

The Test Scores table contains Name, Score, and Test Date for 12 students. A better mobile representation is a **card list grouped by Test Date**, since many students share the same test date:

```
06/23/2011
┌───────────────────────────┐
│ Bob        84  ●●●●○      │
│ Daniel     80  ●●●●○      │
│ Frank      81  ●●●●○      │
│ Gene       92  ●●●●●      │
│ Kristen    83  ●●●●○      │
│ Lois       99  ●●●●●      │
│ Mandy     100  ●●●●●      │
└───────────────────────────┘

07/14/2011
┌───────────────────────────┐
│ Amy        77  ●●●●○      │
│ Chris      95  ●●●●●      │
│ Holly      67  ●●●○○      │
│ Ivan       79  ●●●●○      │
└───────────────────────────┘
```

Grouping reduces redundant repetition of the date, each row is a touch-friendly height, and a visual score bar (or color-coded badge) lets users scan performance without reading every number.

---

**Batch 20 MAD Quiz 3 — Q6**

Column alignment creates a consistent vertical axis that the human eye can scan rapidly without reading individual values. Consider a score column: if all numbers are right-aligned, a user can glance down the column and immediately spot the highest and lowest values by their visual weight and position. If values are randomly positioned, the eye must stop at each cell, parse its position, then move to the next — essentially reading every entry individually.

Misaligned columns also break the implicit grid structure that gives tables their meaning. When cells are scattered at different x-positions, the visual grouping that tells the user "these values belong to the same attribute" is destroyed. On a small mobile screen where there is already spatial pressure, lost alignment means lost comprehension. Consistent column alignment is therefore not a cosmetic preference — it is a functional requirement for data scannability.

---

**Batch 20 MAD Quiz 3 — Q7**

ILHAM's problem is the classic "lost row header during horizontal scroll" issue with wide tables. The solution is the **Frozen/Sticky Column pattern**.

Keep the leftmost column (team name) fixed in place while only the remaining data columns scroll horizontally inside a nested scroll container. The team name never moves, so no matter how far right the user scrolls to check goals, passes, or substitutes, they always know which team's row they are on.

Implementation concept:
```
┌──────────┬──────────────────────────────────────────────→ scroll
│ Team     │  Goals │ Passes │ Misses │ Crosses │ Subs │ ...
│ ──────── │ ────── │ ────── │ ─────  │ ─────── │ ─── │
│ Team A   │   3    │   42   │   8    │   12    │  2  │
│ Team B   │   1    │   30   │   15   │   9     │  3  │
└──────────┴─────────────────────────────────────────────
  (fixed)    (scrolls horizontally)
```

The left column sits outside the horizontal ScrollView, rendered in a separate fixed-width View that overlays or sits adjacent to the scrollable section.

---

**Batch 20 MAD Quiz 3 — Q8**

When a user taps a cell in an editable table, the mobile keyboard activates and covers roughly the bottom half of the screen. This leaves only a fraction of the table visible, so the user has lost visual context of the surrounding data. Additionally, there is no Tab key on mobile to navigate between cells sequentially — the user must dismiss the keyboard, scroll to the next cell, tap it, wait for the keyboard to reappear, and repeat for every single entry. For a table with dozens of editable cells this workflow is impractically tedious and error-prone.

---

**Batch 20 MAD Quiz 3 — Q9**

**Technique 1 — Ensure the parent has flex:1 or a defined height:**
A ScrollView inherits its height from its parent. If the parent has no explicit height or `flex: 1`, it collapses to zero height and the ScrollView, though mounted, has no space to render into. Fix by applying `flex: 1` to every View ancestor up the tree from the ScrollView to the root.
```javascript
// Before (broken)
<View>
  <ScrollView><Text>Hello</Text></ScrollView>
</View>

// After (fixed)
<View style={{ flex: 1 }}>
  <ScrollView><Text>Hello</Text></ScrollView>
</View>
```

**Technique 2 — Add a visible background color to isolate the problem:**
Temporarily add `backgroundColor: 'red'` to the ScrollView's style. If a red area appears, the ScrollView has dimensions but its children have no size. Then add `backgroundColor: 'blue'` to the children — if blue appears, the children exist but may be positioned off-screen. If no red appears, the issue is in the parent's dimensions as described above. This technique isolates whether the problem is the ScrollView itself, its container, or its children, without needing an external debugger.

---

**Batch 20 MAD Quiz 3 — Q10**

**1. visible** (boolean) — Controls whether the Modal is rendered and shown over the current screen. Setting it to `true` displays the modal; `false` hides it. Typically driven by a state variable.

**2. animationType** (string) — Determines how the modal appears and disappears. `'none'` shows it instantly, `'slide'` slides it up from the bottom edge, and `'fade'` fades it in gradually.

**3. transparent** (boolean) — When `true`, the modal's background is transparent rather than a solid default color, so the screen behind it remains partially or fully visible. Used for overlay dialogs.

**4. onRequestClose** (function) — A callback invoked when the user presses the hardware Back button on Android or the close gesture on some iOS presentations. On Android this prop is required to prevent the app from doing nothing on back press while the modal is open.

**5. onShow** (function) — A callback invoked once the modal has fully appeared and become visible to the user. Useful for triggering an animation, focusing an input field, or fetching data immediately after the modal opens.