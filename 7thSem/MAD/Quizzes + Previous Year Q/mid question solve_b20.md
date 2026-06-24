---

## Question 1

### a) React vs. Classic HTML, JS, CSS Approach

Neither approach is universally "the best"; the ideal choice depends completely on the project requirements.

* **Classic Approach (HTML, CSS, JS):** * **Pros:** Ideal for static websites, landing pages, or content-centric sites. It offers faster initial page loads (no heavy framework bundle to download) and superior out-of-the-box SEO.
* **Cons:** Hard to maintain for large-scale, highly interactive dynamic Single Page Applications (SPAs) because manual DOM manipulation becomes tedious and bug-prone.


* **React Approach:** * **Pros:** Excellent for dynamic, state-heavy web applications. It uses a **Virtual DOM** to optimize rendering updates, offers a highly reusable component-based architecture, and simplifies complex UI state management.
* **Cons:** Adds initial bundle size overhead and requires a modern build compilation step (Webpack/Vite).



**Justification:** If Atiq and Shafin are building a simple portfolio or informational site, the classic approach is best. If they are building an interactive dashboard or a SaaS platform, React is the superior choice.

---

### b) Difference Between `var` and `let`

* **Scope:** `var` is **function-scoped** (or global), meaning it ignores block boundaries like `if` or `for`. `let` is strictly **block-scoped** (bounded by `{}`).
* **Hoisting:** Both are hoisted, but `var` variables are initialized with `undefined`, whereas `let` variables are placed in a Temporal Dead Zone (TDZ) and cannot be accessed before initialization.

#### Stack Procedure / Scope Chain Trace:

1. **Global Frame:** `v1` (10) and `l2` (17) are pushed.
2. **Function Frame (`f1`):** `v0` (9) and `l0` (8) are pushed. `v3` is declared with `var`, so it hoists to this function frame level.
3. **Block Frame (`if(1)`):** `l1` (7) is pushed here. `v3` assigns `121` to the variable residing in the parent function frame.
4. **Exiting Block:** `l1` is popped from the stack and destroyed. `v3` remains accessible in the function frame.

#### Output Steps:

* Line 9: `8`
* Line 10: `7`
* Line 11: `10`
* Line 12: `17`
* Line 15: `121`
* Line 18: Throws `ReferenceError: v0 is not defined` *(since `v0` is local to the function frame and cannot be accessed globally)*.

---

### c) JavaScript Output Methods (Other than `console.log`)

1. **`alert()`**: Displays data in an browser pop-up modal box.
2. **`document.write()`**: Appends output directly into the HTML document layout stream.
3. **`innerHTML` property**: Targets and modifies the content of a specific DOM node element (e.g., `document.getElementById('id').innerHTML = value`).
4. **`window.print()`**: Opens the print dialog box to print the current webpage content.

---

### d) Output of Code Snippet 2

The `.filter()` method retains elements for which the condition returns `true`. Here, it checks if string lengths are strictly less than 6.

```json
[ "atiq", "edon" ]

```

---

---

## Question 2

### a) Best Mobile Navigation Pattern for IUTPS

The ideal pattern is the **Bottom Navigation Bar (Tab Bar)**.

#### Justification:

* **High Visibility:** The client explicitly requested that all 3 flat-hierarchy categories remain "always visible for quick access." A bottom bar ensures continuous presence.
* **Horizontal Space Allocation:** Since there are only 3 elements, there is ample horizontal space to handle dynamic text changing seamlessly (e.g., updating a label to `SHOOT-ON-16December`) without compromising the layout.

---

### b) Anti-patterns and Solutions from 312Technology

1. **Anti-pattern 1:** Placing a slide drawer menu at the *bottom* of the screen.
* **Solution:** Drawers should always open from the left or right edge. Alternatively, replace it entirely with a persistent **Bottom Navigation Bar** for the top features.


2. **Anti-pattern 2:** Mixing items of varying importance into a long, scrolling navigation list.
* **Solution:** Extract the most critical core features and move them to a main primary layout tab view. Keep only secondary settings or profile links in a hidden drawer menu.



---

### c) Why Sidebars are Not Considered a Persistent Navigation Pattern on Mobile

1. **Screen Real Estate Constraints:** Mobile layouts lack horizontal width. Keeping a sidebar permanently visible would crowd out primary screen content entirely.
2. **Interactivity Standard:** Mobile drawers are designed to hide off-screen by default to maximize content viewability, requiring a gesture or click action to expose options overlaying the view temporarily.

---

### d) Skeuomorphic Pattern Definition

**Skeuomorphism** is a design system where digital UI elements directly replicate real-world material textures, physics, and designs (e.g., a voice memo app styled like a vintage cassette tape recorder with plastic sheen bevels, raised gloss buttons, and drop-shadows).

---

---

## Question 3

### a) Output of Code Snippet 3

* **Case 1: `id = 8**`
* `(8 % 2) === 0` resolves to `true`, executing the first matching block.
* **Output:** `id is even`


* **Case 2: `id = 27**`
* `(27 % 3) === 0` resolves to `true`, executing its block. Because there is **no `break` statement** after line 6, execution falls through completely into the next case regardless of the conditional outcome.
* **Output:**
```text
id is multiple of 3
id is odd

```





---

### b) Code Snippet 4 Placeholders (`????`)

1. **Line 2:** `'react'`
2. **Line 8:** `useEffect`
3. **Line 29:** `Total Expense`
4. **Line 31:** `View`
5. **Line 34:** `CalculateExpense`

---

### c) Terms with Examples

1. **Asynchronous Programming:** Execution behavior that doesn't block program operations while waiting for long running processing actions.
* *Example:* `fetch('https://api.example.com/data').then(res => res.json())`


2. **Setup Function of `useEffect`:** The initialization block handler containing side-effect routines declared inside the hook.
* *Example:* The function closure `() => { console.log('mounted'); }` inside `useEffect`.


3. **Conditional Rendering:** Displaying UI markup variations conditionally.
* *Example:* `{isLoggedIn ? <Welcome /> : <Login />}`



---

### d) Output of Code Snippet 5

The loop processes elements in the array to sequentially concatenate numbers into string types.

* Note: The provided snippet updates the `txt` variable internally but does not contain a printing call (like `console.log`).

If printed, the final string output value of `txt` is:

```text
45491625

```

---

### e) Difference Between States and Props

| Feature | State | Props |
| --- | --- | --- |
| **Definition** | Managed internally within the component. | Data passed down from a parent component. |
| **Mutability** | Mutable via its dedicated setter state updater function. | Immutable; read-only inside the receiver component. |
| **Re-rendering** | Triggers a visual re-render when updated. | Triggers a visual re-render when parent modifications supply new values. |