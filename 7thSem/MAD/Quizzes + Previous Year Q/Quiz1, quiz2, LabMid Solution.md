**Quiz 1 — Q1 (Fill in the blanks)**

?1? = View
?2? = StyleSheet
?3? = react
?4? = Enter Text (or any appropriate title string, e.g. "Text Input Example")
?5? = placeholder
?6? = textInput
?7? = setInputText
?8? = inputText
?9? = text
?10? = View
?11? = center
?12? = column
?13? = any valid color string, e.g. 'blue'

---

**Quiz 1 — Q2**

Two approaches for implementing platform-specific files in React Native:

1. **Platform-specific file extensions** — Create separate files named `Component.ios.js` and `Component.android.js`. React Native automatically picks the correct file based on the platform at build time.

2. **Platform module** — Use `Platform.OS` (e.g. `Platform.OS === 'ios'`) or `Platform.select({ ios: ..., android: ... })` inside a single file to conditionally apply platform-specific logic or styles.

---

**Lab Mid — MCQ Answers**

1. flex-center
2. 25
3. margin: 10
4. padding: 10
5. ImageBackground
6. Yes
7. style={[styles.textStyle, styles.largeText]}
8. Undefined (no return statement, so the function implicitly returns undefined)
9. useState
10. useEffect
11. setCount(count+1)
12. The component re-renders
13. To pass data from parent to children component
14. Yes
15. justifyContent (main axis is vertical when flexDirection is column)
16. "Village" (name is string "10", strict equality with number 10 is false)
17. Only once after mounting
18. It uses native components like \<View\> and \<Text\>
19. ScrollView
20. Adds a new message while preserving existing messages

---

**Quiz 2 — Q1 (Three design and usability problems)**

**Problem 1: Inadequate Navigation Structure**
The app lacks a clearly visible and persistent navigation mechanism. Students report difficulty moving between Courses, Assignments, Results, and Messages, which indicates the navigation is either buried in menus, requires multiple taps, or is inconsistent across screens. On mobile, users rely on spatial memory and must be able to orient themselves and switch sections effortlessly. Without a structured navigation pattern, the cognitive load increases significantly, reducing overall usability.

**Problem 2: Inappropriate Presentation of Grade Data on Mobile**
Grade reports are rendered as large traditional tables, which are fundamentally mismatched with mobile screen constraints. Tables require horizontal scrolling, force users to zoom in to read content, and break visual hierarchy on small displays. Mobile interfaces demand concise, vertically-scrollable, visually scannable layouts. Displaying dense tabular data without reformatting it for mobile leads to poor readability and user frustration.

**Problem 3: No Mechanism for Quick Access to Frequently Used Features**
Students cannot quickly locate features they use most often, implying the app offers no prioritized entry point or shortcut layer. On mobile, high-frequency tasks should require minimal taps to reach. Without a dedicated home or dashboard view, all modules are treated equally, forcing users to navigate the same depth every time regardless of how often they use a feature. This increases task completion time and decreases efficiency.

---

**Quiz 2 — Q2 (Recommended patterns)**

**For Problem 1 — Tab Menu Pattern**
A bottom tab bar with icons and labels for each primary module (Courses, Assignments, Results, Messages) should be implemented. This pattern keeps navigation persistently visible at the bottom of every screen, which is within easy thumb reach on mobile. Users can switch between sections in a single tap from anywhere in the app, eliminating the disorientation they currently experience. Since the app has exactly four major modules, a tab menu is ideally sized — typically suited for 3–5 top-level destinations.

**For Problem 2 — Card-based Data Visualization Pattern**
Replace the traditional grade tables with card components presenting each course's grade as a summary unit — including the grade value, a progress bar or mini chart, and status indicators. Cards stack vertically, are fully readable without scrolling horizontally, and allow users to scan performance at a glance. For detailed breakdown, a card can expand or link to a dedicated screen. This respects mobile screen real estate while making the same data far more interpretable.

**For Problem 3 — Dashboard Pattern**
A home dashboard screen should be introduced as the app's landing view. It surfaces contextually relevant, high-frequency information such as upcoming assignment deadlines, recent announcements, unread messages, and current grades in a glanceable layout. Quick-action buttons for the most-used tasks can be embedded directly on the dashboard. This reduces the number of taps required for routine tasks, helps users immediately understand what needs their attention, and removes the burden of remembering where each feature is located in the app hierarchy.