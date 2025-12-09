document.getElementById('f').addEventListener('change', async (e) => {
  const file = e.target.files[0];
  if (!file) return;

  const form = new FormData();
  form.append('file', file);

  const res = await fetch('./upload', { method: 'POST', body: form });
  document.getElementById('out').textContent = await res.text();
});
