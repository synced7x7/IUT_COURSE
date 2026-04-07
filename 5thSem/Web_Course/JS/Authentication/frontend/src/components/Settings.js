import { useAuth } from "../context/AuthContext";

export default function Settings() {
  const { token } = useAuth();

  console.log("JWT:", token);

  return (
    <div>
      <h2>Settings Page</h2>
      <p>This is another protected page.</p>
    </div>
  );
}